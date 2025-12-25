#include "Application.h"
#include "Parser.h"
#include "StateFactory.h"
#include "Toolbar.h"
#include "GroupCommand.h"
#include "MoveCommand.h"
#include "Constants.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace geom
{

    // Реализация шаблона Singleton
    Application& Application::GetInstance()
    {
        static Application instance;
        return instance;
    }

    Application::Application()
        : m_dragging(false)
        , m_commandHistoryIndex(0)
        , m_totalDragX(0.0f)
        , m_totalDragY(0.0f)
    {
    }

    // Шаблон Facade: инициализация всех подсистем
    void Application::Initialize(const std::string& inputPath, const std::string& outputPath)
    {
        m_inputPath = inputPath;
        m_outputPath = outputPath;

        // Парсинг входного файла
        Parser parser;
        m_shapes = parser.ParseFile(m_inputPath);
        parser.WriteResults(m_outputPath, m_shapes);

        // ОЧИСТИТЬ ИСТОРИЮ КОМАНД - теперь начальное состояние считается "точкой отсчета"
        m_commandHistory.clear();
        m_commandHistoryIndex = 0;

        // Создание SFML окна
        m_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(sf::Vector2u(Constants::WINDOW_WIDTH,
                Constants::WINDOW_HEIGHT)),
            Constants::WINDOW_TITLE
        );
        m_window->setFramerateLimit(Constants::FRAME_RATE_LIMIT);

        // Создание панели инструментов
        m_toolbar = std::make_unique<Toolbar>(*this);

        // Установка начального состояния
        m_currentState = StateFactory::CreateState(EditorMode::Select, *this);
    }

    // Основной цикл приложения
    void Application::Run()
    {
        if (!m_window)
        {
            return;
        }

        while (m_window->isOpen())
        {
            ProcessEvents();
            Render();
        }
    }

    void Application::Shutdown()
    {
        if (m_window)
        {
            m_window->close();
        }
    }

    void Application::ProcessEvents()
    {
        while (auto event = m_window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window->close();
            }
            else if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (auto mb = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    HandleMouseButtonPressed(*mb);
                }
            }
            else if (event->is<sf::Event::MouseButtonReleased>())
            {
                if (auto mb = event->getIf<sf::Event::MouseButtonReleased>())
                {
                    HandleMouseButtonReleased(*mb);
                }
            }
            else if (event->is<sf::Event::MouseMoved>())
            {
                if (auto mm = event->getIf<sf::Event::MouseMoved>())
                {
                    HandleMouseMoved(*mm);
                }
            }
            else if (event->is<sf::Event::KeyPressed>())
            {
                if (auto kp = event->getIf<sf::Event::KeyPressed>())
                {
                    HandleKeyPressed(*kp);
                }
            }
        }
    }

    void Application::HandleMouseButtonPressed(const sf::Event::MouseButtonPressed& event)
    {
        if (event.button != sf::Mouse::Button::Left)
        {
            return;
        }

        const sf::Vector2f pos(
            static_cast<float>(event.position.x),
            static_cast<float>(event.position.y)
        );

        // Проверяем, был ли клик на панели инструментов (переключение состояний)
        bool toolbarClicked = false;
        if (m_toolbar)
        {
            const auto tbBounds = m_toolbar->GetBounds();
            if (pos.x >= tbBounds.position.x &&
                pos.x <= tbBounds.position.x + tbBounds.size.x &&
                pos.y >= tbBounds.position.y &&
                pos.y <= tbBounds.position.y + tbBounds.size.y)
            {
                m_toolbar->HandleClick(pos);
                toolbarClicked = true;
            }
        }

        if (!toolbarClicked && m_currentState)
        {
            // Делегируем текущему состоянию (State Pattern)
            m_currentState->OnMousePress(pos);

            // Начинаем перетаскивание, если в режиме выделения
            if (m_currentState->GetMode() == EditorMode::Select && !m_selected.empty())
            {
                // Сохраняем начальные позиции для команды отмены
                m_dragStartPositions.clear();
                for (const auto& shape : m_selected)
                {
                    auto bounds = shape->GetBounds();
                    m_dragStartPositions.push_back(
                        sf::Vector2f(bounds.position.x, bounds.position.y)
                    );
                }

                m_dragging = true;
                m_lastMousePos = pos;
                m_dragDropManager.StartDragging(pos);
            }
        }
    }


    void Application::HandleMouseMoved(const sf::Event::MouseMoved& event)
    {
        const sf::Vector2f pos(
            static_cast<float>(event.position.x),
            static_cast<float>(event.position.y)
        );

        if (m_currentState)
        {
            m_currentState->OnMouseMove(pos);
        }

        // Визуальное перетаскивание в реальном времени
        if (m_dragging && !m_selected.empty())
        {
            // Вычисляем смещение мыши с последней позиции
            const float dx = pos.x - m_lastMousePos.x;
            const float dy = pos.y - m_lastMousePos.y;

            // Если смещение достаточно велико
            if (std::abs(dx) > 0.01f || std::abs(dy) > 0.01f)
            {
                // Используем DragDropManager для визуального перемещения
                m_dragDropManager.UpdateDragging(pos, m_selected);

                // Обновляем накопленное смещение для создания команды позже
                m_totalDragX += dx;
                m_totalDragY += dy;

                m_lastMousePos = pos;
            }
        }
    }

    void Application::HandleMouseButtonReleased(const sf::Event::MouseButtonReleased& event)
    {
        if (event.button != sf::Mouse::Button::Left)
        {
            return;
        }

        const sf::Vector2f pos(
            static_cast<float>(event.position.x),
            static_cast<float>(event.position.y)
        );

        // Завершаем перетаскивание и создаем команду
        if (m_dragging && !m_selected.empty())
        {
            m_dragDropManager.StopDragging();

            // Проверяем, было ли достаточно большое перемещение
            if (std::abs(m_totalDragX) > Constants::MIN_DRAG_THRESHOLD ||
                std::abs(m_totalDragY) > Constants::MIN_DRAG_THRESHOLD)
            {
                // Копируем выбранные фигуры для команды
                std::vector<std::shared_ptr<IGeometry>> shapesToMove;
                shapesToMove.reserve(m_selected.size());
                for (const auto& shape : m_selected)
                {
                    shapesToMove.push_back(shape);
                }

                // СОЗДАЕМ КОМАНДУ ДЛЯ ОТМЕНЫ ПЕРЕМЕЩЕНИЯ
                // Указываем смещение, на которое уже переместили фигуры
                auto cmd = std::make_unique<MoveCommand>(
                    std::move(shapesToMove),
                    m_totalDragX,  // Смещение, которое уже выполнено
                    m_totalDragY   // Смещение, которое уже выполнено
                );

                // ВАЖНО: команда уже "выполнена" (фигуры уже перемещены)
                // Поэтому помечаем ее как выполненную
                cmd->MarkAsExecuted(); // Нужно добавить этот метод в MoveCommand

                ExecuteCommand(std::move(cmd));
            }

            m_dragging = false;
            m_totalDragX = 0.0f;
            m_totalDragY = 0.0f;
            m_dragStartPositions.clear();
        }

        if (m_currentState)
        {
            m_currentState->OnMouseRelease(pos);
        }
    }

    void Application::HandleKeyPressed(const sf::Event::KeyPressed& event)
    {
        const bool ctrl = event.control || event.system ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl);

        if (!ctrl) return;

        // Используем switch-case для лучшей читаемости
        switch (event.scancode)
        {
        case sf::Keyboard::Scancode::Z:
            Undo();
            break;

        case sf::Keyboard::Scancode::Y:
        case sf::Keyboard::Scancode::R:
            Redo();  // Ctrl+Y или Ctrl+R для повтора
            break;

        case sf::Keyboard::Scancode::G:
            if (m_selected.size() >= 2)
            {
                auto cmd = std::make_unique<GroupCommand>(
                    GroupCommand::Operation::Group,
                    m_shapes,
                    m_selected
                );
                ExecuteCommand(std::move(cmd));
            }
            break;

        case sf::Keyboard::Scancode::U:
            if (m_selected.size() == 1)
            {
                if (auto group = std::dynamic_pointer_cast<CompositeShape>(m_selected[0]))
                {
                    auto cmd = std::make_unique<GroupCommand>(
                        GroupCommand::Operation::Ungroup,
                        m_shapes,
                        m_selected
                    );
                    ExecuteCommand(std::move(cmd));
                }
            }
            break;

        default:
            // Другие клавиши не обрабатываются
            break;
        }
    }

    void Application::CreateMoveCommandForDragDrop()
    {
    //    // Используем накопленное перемещение для создания команды
    //    // Не вычисляем заново, используем уже накопленные значения
    //    if (std::abs(m_totalDragX) < Constants::MIN_DRAG_THRESHOLD &&
    //        std::abs(m_totalDragY) < Constants::MIN_DRAG_THRESHOLD)
    //        return;

    //    // Копируем выбранные фигуры для команды
    //    std::vector<std::shared_ptr<IGeometry>> shapesToMove;
    //    shapesToMove.reserve(m_selected.size());
    //    for (const auto& shape : m_selected)
    //    {
    //        shapesToMove.push_back(shape);
    //    }

    //    // Создаем и выполняем команду Command Pattern
    //    auto cmd = std::make_unique<MoveCommand>(
    //        std::move(shapesToMove),
    //        m_totalDragX,
    //        m_totalDragY
    //    );

    //    ExecuteCommand(std::move(cmd));
    }

    void Application::Render()
    {
        m_window->clear(Constants::BACKGROUND_COLOR);

        if (m_toolbar)
        {
            m_toolbar->Draw(*m_window);
        }

        for (const auto& shape : m_shapes)
        {
            shape->Draw(*m_window);
        }

        // Отрисовка рамок выделения
        for (const auto& selected : m_selected)
        {
            const auto bounds = selected->GetBounds();
            sf::RectangleShape box(sf::Vector2f(bounds.size.x, bounds.size.y));
            box.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
            box.setFillColor(sf::Color::Transparent);
            box.setOutlineColor(Constants::SELECTION_COLOR);
            box.setOutlineThickness(Constants::SELECTION_OUTLINE_THICKNESS);
            m_window->draw(box);
        }

        m_window->display();
    }

    // Facade Methods 

    void Application::AddShape(std::shared_ptr<IGeometry> shape)
    {
        m_shapes.push_back(shape);
    }

    void Application::RemoveShape(std::shared_ptr<IGeometry> shape)
    {
        m_shapes.erase(
            std::remove(m_shapes.begin(), m_shapes.end(), shape),
            m_shapes.end()
        );
    }

    void Application::SelectShape(std::shared_ptr<IGeometry> shape, bool addToSelection)
    {
        if (!addToSelection)
        {
            m_selected.clear();
        }

        if (std::find(m_selected.begin(), m_selected.end(), shape) == m_selected.end())
        {
            m_selected.push_back(shape);
        }
    }

    void Application::ClearSelection()
    {
        m_selected.clear();
    }

    void Application::SetState(std::unique_ptr<IEditorState> state)
    {
        m_currentState = std::move(state);
    }

    EditorMode Application::GetCurrentMode() const
    {
        return m_currentState ? m_currentState->GetMode() : EditorMode::Select;
    }

    // Command Pattern: выполнение команды и управление историей
    void Application::ExecuteCommand(std::unique_ptr<ICommand> cmd)
    {
        if (!cmd)
        {
            return;
        }

        // Обрезаем историю, если не в конце (для перезаписи redo)
        if (m_commandHistoryIndex < m_commandHistory.size())
        {
            m_commandHistory.resize(m_commandHistoryIndex);
        }

        cmd->Execute();
        m_commandHistory.push_back(std::move(cmd));
        m_commandHistoryIndex = m_commandHistory.size();

        // Ограничим размер истории (опционально, чтобы не росла бесконечно)
        const size_t MAX_HISTORY_SIZE = 50;
        if (m_commandHistory.size() > MAX_HISTORY_SIZE)
        {
            m_commandHistory.erase(m_commandHistory.begin());
            m_commandHistoryIndex--;
        }
    }

    // Command Pattern: отмена последней команды
    void Application::Undo()
    {
        if (m_commandHistoryIndex > 0)
        {
            --m_commandHistoryIndex;

            if (m_commandHistoryIndex < m_commandHistory.size())
            {
                m_commandHistory[m_commandHistoryIndex]->Undo();
            }
            else
            {
                // Если индекс вне границ, сбрасываем историю
                m_commandHistory.clear();
                m_commandHistoryIndex = 0;
            }
        }
        else if (m_commandHistoryIndex == 0 && !m_commandHistory.empty())
        {
            // Особый случай: отмена самой первой команды
            m_commandHistory[0]->Undo();
            m_commandHistoryIndex = 0; // остаемся на 0
        }
    }

    // Command Pattern: повтор последней отмененной команды
    void Application::Redo()
    {
        if (m_commandHistoryIndex < m_commandHistory.size())
        {
            m_commandHistory[m_commandHistoryIndex]->Execute();
            ++m_commandHistoryIndex;
        }
    }

}