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
    // Singleton Pattern implementation
    Application& Application::GetInstance()
    {
        static Application instance;
        return instance;
    }

    // Facade Pattern: initialize all subsystems
    void Application::Initialize(const std::string& inputPath, const std::string& outputPath)
    {
        m_inputPath = inputPath;
        m_outputPath = outputPath;

        // Parse input file
        Parser parser;
        m_shapes = parser.ParseFile(m_inputPath);
        parser.WriteResults(m_outputPath, m_shapes);

        // Create SFML window
        m_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(sf::Vector2u(Constants::WINDOW_WIDTH,
                Constants::WINDOW_HEIGHT)),
            Constants::WINDOW_TITLE
        );
        m_window->setFramerateLimit(Constants::FRAME_RATE_LIMIT);

        // Create toolbar (uses State Pattern)
        m_toolbar = std::make_unique<Toolbar>(*this);

        // Set initial state (Select mode)
        m_currentState = StateFactory::CreateState(EditorMode::Select, *this);
    }

    // Main application loop
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

        // Check if click is on toolbar (State Pattern switching)
        bool toolbarClicked = false;
        if (m_toolbar)
        {
            const auto tbBounds = m_toolbar->GetBounds();
            if (pos.x >= tbBounds.position.x &&
                pos.x <= tbBounds.position.x + tbBounds.size.x &&
                pos.y >= tbBounds.position.y &&
                pos.y <= tbBounds.position.y + tbBounds.size.y)
            {
                m_toolbar->HandleClick(pos);  // This may change state via State Pattern
                toolbarClicked = true;
            }
        }

        if (!toolbarClicked && m_currentState)
        {
            // Delegate to current state (State Pattern)
            m_currentState->OnMousePress(pos);

            // Start dragging if in Select mode
            if (m_currentState->GetMode() == EditorMode::Select && !m_selected.empty())
            {
                // Save initial positions for undo command
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

        // Complete dragging and create Command Pattern command
        if (m_dragging && !m_selected.empty() && !m_dragStartPositions.empty())
        {
            CreateMoveCommandForDragDrop();  // Creates MoveCommand
            m_dragStartPositions.clear();
        }

        m_dragging = false;

        if (m_currentState)
        {
            m_currentState->OnMouseRelease(pos);
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

        // Handle real-time dragging (visual feedback)
        if (m_dragging && !m_selected.empty())
        {
            const float dx = pos.x - m_lastMousePos.x;
            const float dy = pos.y - m_lastMousePos.y;

            if (dx != 0.0f || dy != 0.0f)
            {
                for (auto& shape : m_selected)
                {
                    shape->MoveBy(dx, dy);
                }
                m_lastMousePos = pos;
            }
        }
    }

    void Application::HandleKeyPressed(const sf::Event::KeyPressed& event)
    {
        const bool ctrl = event.control || event.system ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl);

        if (!ctrl) return;

        // Use switch-case for better readability
        switch (event.scancode)
        {
        case sf::Keyboard::Scancode::Z:
        case sf::Keyboard::Scancode::Y:
            Undo();
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
            // Other keys not handled
            break;
        }
    }

    void Application::CreateMoveCommandForDragDrop()
    {
        // Calculate total movement for Command Pattern
        float totalDx = 0.0f;
        float totalDy = 0.0f;
        int movedCount = 0;

        for (size_t i = 0; i < m_selected.size(); ++i)
        {
            auto bounds = m_selected[i]->GetBounds();
            float dx = bounds.position.x - m_dragStartPositions[i].x;
            float dy = bounds.position.y - m_dragStartPositions[i].y;

            if (std::abs(dx) > Constants::MIN_DRAG_THRESHOLD ||
                std::abs(dy) > Constants::MIN_DRAG_THRESHOLD)
            {
                totalDx += dx;
                totalDy += dy;
                movedCount++;
            }
        }

        if (movedCount > 0)
        {
            float avgDx = totalDx / movedCount;
            float avgDy = totalDy / movedCount;

            std::vector<std::shared_ptr<IGeometry>> shapesToMove;
            shapesToMove.reserve(m_selected.size());
            for (const auto& shape : m_selected)
            {
                shapesToMove.push_back(shape);
            }

            // Create and execute Command Pattern command
            auto cmd = std::make_unique<MoveCommand>(
                std::move(shapesToMove),
                avgDx,
                avgDy
            );

            ExecuteCommand(std::move(cmd));
        }
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

        // Draw selection boxes
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

    // ==================== Facade Methods ====================

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

    // Command Pattern: execute command and manage history
    void Application::ExecuteCommand(std::unique_ptr<ICommand> cmd)
    {
        if (!cmd)
        {
            return;
        }

        // Truncate history if not at the end (for redo overwrite)
        if (m_commandHistoryIndex < m_commandHistory.size())
        {
            m_commandHistory.resize(m_commandHistoryIndex);
        }

        cmd->Execute();
        m_commandHistory.push_back(std::move(cmd));
        m_commandHistoryIndex = m_commandHistory.size();
    }

    // Command Pattern: undo last command
    void Application::Undo()
    {
        if (m_commandHistoryIndex > 0)
        {
            --m_commandHistoryIndex;

            if (m_commandHistoryIndex < m_commandHistory.size())
            {
                try
                {
                    m_commandHistory[m_commandHistoryIndex]->Undo();
                }
                catch (...)
                {
                    // Если команда не может быть отменена (например, фигуры удалены)
                    // Удаляем её из истории
                    m_commandHistory.erase(m_commandHistory.begin() + m_commandHistoryIndex);
                    m_commandHistoryIndex = m_commandHistory.size();
                }
            }
            else
            {
                // Индекс вне границ - сбрасываем историю
                m_commandHistory.clear();
                m_commandHistoryIndex = 0;
            }
        }
    }
} 