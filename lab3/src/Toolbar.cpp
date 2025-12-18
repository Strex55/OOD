#include "Toolbar.h"
#include "Application.h"
#include "StateFactory.h"
#include "ChangeStyleCommand.h"
#include "Constants.h"
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>

namespace geom
{

    // Загружает шрифт для отображения текста
    int Toolbar::LoadFont()
    {
        // Пробуем несколько путей к стандартным шрифтам Windows
        std::vector<std::string> fontPaths = {
            "C:/Windows/Fonts/arial.ttf",      // Стандартный путь
            "C:/Windows/Fonts/ARIAL.TTF",      // Верхний регистр
            "C:/Windows/Fonts/Arial.ttf",      // Смешанный регистр
            "C:/Windows/Fonts/tahoma.ttf",     // Альтернативный шрифт
            "C:/Windows/Fonts/segoeui.ttf",    // Современный шрифт Windows
            "arial.ttf",                        // Текущая директория
            "./arial.ttf"                       // Текущая директория
        };

        for (const auto& path : fontPaths)
        {
            if (m_font.openFromFile(path))
            {
                return 1; // Успешная загрузка шрифта
            }
        }

        std::cerr << "Не удалось загрузить ни один шрифт. Текст не будет отображаться." << std::endl;
        return 0; // Ошибка загрузки шрифта
    }

    Toolbar::Toolbar(Application& app) : m_app(app)
    {
        LoadFont(); // Просто вызываем, не сохраняя результат

        m_background.setSize(sf::Vector2f(1000.0f, Constants::TOOLBAR_HEIGHT));
        m_background.setPosition(sf::Vector2f(0, 0));
        m_background.setFillColor(sf::Color(240, 240, 240));
        m_background.setOutlineColor(sf::Color(200, 200, 200));
        m_background.setOutlineThickness(1.0f);

        InitializeToolButtons();
        InitializeColorButtons();
        InitializeThicknessButtons();
    }

    void Toolbar::InitializeToolButtons()
    {
        // Используем константы из Constants.h
        const int numTools = static_cast<int>(Constants::TOOL_NAMES.size());
        m_toolButtons.resize(numTools);
        m_toolLabels.clear();
        m_toolLabels.reserve(numTools);

        for (int i = 0; i < numTools; ++i)
        {
            m_toolButtons[i].setSize(sf::Vector2f(Constants::BUTTON_SIZE, Constants::BUTTON_SIZE));
            m_toolButtons[i].setPosition(sf::Vector2f(
                Constants::BUTTON_SPACING + i * (Constants::BUTTON_SIZE + Constants::BUTTON_SPACING),
                Constants::BUTTON_SPACING
            ));
            m_toolButtons[i].setFillColor(sf::Color(220, 220, 220));
            m_toolButtons[i].setOutlineColor(sf::Color::Black);
            m_toolButtons[i].setOutlineThickness(1.0f);

            // Создание текста метки
            m_toolLabels.emplace_back(m_font, sf::String(Constants::TOOL_NAMES[i]), 12);
            m_toolLabels[i].setFillColor(sf::Color::Black);

            // Центрирование текста на кнопке
            const auto btnPos = m_toolButtons[i].getPosition();
            const auto btnSize = m_toolButtons[i].getSize();
            const auto textBounds = m_toolLabels[i].getLocalBounds();

            float textWidth = textBounds.size.x;
            float textHeight = textBounds.size.y;
            float textLeft = textBounds.position.x;
            float textTop = textBounds.position.y;

            m_toolLabels[i].setPosition(sf::Vector2f(
                btnPos.x + (btnSize.x - textWidth) / 2.0f - textLeft,
                btnPos.y + (btnSize.y - textHeight) / 2.0f - textTop
            ));
        }
    }

    void Toolbar::InitializeColorButtons()
    {
        // Доступные цвета из Constants.h
        m_colorButtons.resize(Constants::AVAILABLE_COLORS.size());
        const float colorStartX = 5 * (Constants::BUTTON_SIZE + Constants::BUTTON_SPACING) + 20.0f;

        for (size_t i = 0; i < Constants::AVAILABLE_COLORS.size(); ++i)
        {
            m_colorButtons[i].setSize(sf::Vector2f(Constants::BUTTON_SIZE * 0.7f, Constants::BUTTON_SIZE * 0.7f));
            m_colorButtons[i].setPosition(sf::Vector2f(
                colorStartX + static_cast<float>(i) * (Constants::BUTTON_SIZE * 0.7f + Constants::BUTTON_SPACING),
                Constants::BUTTON_SPACING * 2.0f
            ));
            m_colorButtons[i].setFillColor(Constants::AVAILABLE_COLORS[i]);
            m_colorButtons[i].setOutlineColor(sf::Color::Black);
            m_colorButtons[i].setOutlineThickness(1.0f);
        }
    }

    void Toolbar::InitializeThicknessButtons()
    {
        // Доступные толщины из Constants.h
        m_thicknessButtons.resize(Constants::AVAILABLE_THICKNESSES.size());
        m_thicknessLabels.clear();
        m_thicknessLabels.reserve(Constants::AVAILABLE_THICKNESSES.size());

        const float colorStartX = 5 * (Constants::BUTTON_SIZE + Constants::BUTTON_SPACING) + 20.0f;
        const float thicknessStartX = colorStartX + Constants::AVAILABLE_COLORS.size() *
            (Constants::BUTTON_SIZE * 0.7f + Constants::BUTTON_SPACING) + 20.0f;

        for (size_t i = 0; i < Constants::AVAILABLE_THICKNESSES.size(); ++i)
        {
            m_thicknessButtons[i].setSize(sf::Vector2f(Constants::BUTTON_SIZE * 0.7f, Constants::BUTTON_SIZE * 0.7f));
            m_thicknessButtons[i].setPosition(sf::Vector2f(
                thicknessStartX + static_cast<float>(i) * (Constants::BUTTON_SIZE * 0.7f + Constants::BUTTON_SPACING),
                Constants::BUTTON_SPACING * 2.0f
            ));
            m_thicknessButtons[i].setFillColor(sf::Color(180, 180, 180));
            m_thicknessButtons[i].setOutlineColor(sf::Color::Black);
            m_thicknessButtons[i].setOutlineThickness(1.0f);

            // Создание метки толщины
            std::string thicknessStr = std::to_string(static_cast<int>(Constants::AVAILABLE_THICKNESSES[i]));
            m_thicknessLabels.emplace_back(m_font, sf::String(thicknessStr), 12);
            m_thicknessLabels[i].setFillColor(sf::Color::Black);

            // Центрирование текста на кнопке
            const auto btnPos = m_thicknessButtons[i].getPosition();
            const auto btnSize = m_thicknessButtons[i].getSize();
            const auto textBounds = m_thicknessLabels[i].getLocalBounds();

            float textWidth = textBounds.size.x;
            float textHeight = textBounds.size.y;
            float textLeft = textBounds.position.x;
            float textTop = textBounds.position.y;

            m_thicknessLabels[i].setPosition(sf::Vector2f(
                btnPos.x + (btnSize.x - textWidth) / 2.0f - textLeft,
                btnPos.y + (btnSize.y - textHeight) / 2.0f - textTop
            ));
        }
    }

    // Возвращает 1 при успешной отрисовке
    int Toolbar::Draw(sf::RenderTarget& target)
    {
        target.draw(m_background);

        // Отрисовка кнопок инструментов с метками
        for (size_t i = 0; i < m_toolButtons.size(); ++i)
        {
            if (i == static_cast<size_t>(m_selectedToolIndex))
            {
                m_toolButtons[i].setOutlineColor(sf::Color::Blue);
                m_toolButtons[i].setOutlineThickness(2.0f);
            }
            else
            {
                m_toolButtons[i].setOutlineColor(sf::Color::Black);
                m_toolButtons[i].setOutlineThickness(1.0f);
            }
            target.draw(m_toolButtons[i]);

            // Отрисовка метки
            if (i < m_toolLabels.size())
            {
                target.draw(m_toolLabels[i]);
            }
        }

        // Отрисовка кнопок цветов
        for (size_t i = 0; i < m_colorButtons.size(); ++i)
        {
            if (i == static_cast<size_t>(m_selectedColorIndex))
            {
                m_colorButtons[i].setOutlineColor(sf::Color::Blue);
                m_colorButtons[i].setOutlineThickness(2.0f);
            }
            else
            {
                m_colorButtons[i].setOutlineColor(sf::Color::Black);
                m_colorButtons[i].setOutlineThickness(1.0f);
            }
            target.draw(m_colorButtons[i]);
        }

        // Отрисовка кнопок толщины
        for (size_t i = 0; i < m_thicknessButtons.size(); ++i)
        {
            if (i == static_cast<size_t>(m_selectedThicknessIndex))
            {
                m_thicknessButtons[i].setOutlineColor(sf::Color::Blue);
                m_thicknessButtons[i].setOutlineThickness(2.0f);
            }
            else
            {
                m_thicknessButtons[i].setOutlineColor(sf::Color::Black);
                m_thicknessButtons[i].setOutlineThickness(1.0f);
            }
            target.draw(m_thicknessButtons[i]);

            // Отрисовка метки
            if (i < m_thicknessLabels.size())
            {
                target.draw(m_thicknessLabels[i]);
            }
        }

        return 1; // Успешная отрисовка
    }

    // Возвращает 1 если клик был обработан, 0 если нет
    int Toolbar::HandleClick(const sf::Vector2f& pos)
    {
        // Отладочный вывод
        // std::cout << "Toolbar click at: " << pos.x << ", " << pos.y << std::endl;

        // Проверка кнопок инструментов (переключение состояний)
        for (size_t i = 0; i < m_toolButtons.size(); ++i)
        {
            const auto& btn = m_toolButtons[i];
            const auto btnPos = btn.getPosition();
            const auto btnSize = btn.getSize();

            // Отладочный вывод
            // std::cout << "Tool button " << i << " bounds: " 
            //           << btnPos.x << "-" << (btnPos.x + btnSize.x) << ", "
            //           << btnPos.y << "-" << (btnPos.y + btnSize.y) << std::endl;

            if (pos.x >= btnPos.x && pos.x <= btnPos.x + btnSize.x &&
                pos.y >= btnPos.y && pos.y <= btnPos.y + btnSize.y)
            {
                m_selectedToolIndex = static_cast<int>(i);
                EditorMode mode = EditorMode::Select;

                switch (i)
                {
                case 0: mode = EditorMode::Select; break;
                case 1: mode = EditorMode::Fill; break;
                case 2: mode = EditorMode::AddTriangle; break;
                case 3: mode = EditorMode::AddRectangle; break;
                case 4: mode = EditorMode::AddCircle; break;
                }

                m_app.SetState(StateFactory::CreateState(mode, m_app));
                return 1; // Клик обработан
            }
        }

        // Проверка кнопок цветов
        for (size_t i = 0; i < m_colorButtons.size(); ++i)
        {
            const auto& btn = m_colorButtons[i];
            const auto btnPos = btn.getPosition();
            const auto btnSize = btn.getSize();

            if (pos.x >= btnPos.x && pos.x <= btnPos.x + btnSize.x &&
                pos.y >= btnPos.y && pos.y <= btnPos.y + btnSize.y)
            {
                m_selectedColorIndex = static_cast<int>(i);
                sf::Color selectedColor = Constants::AVAILABLE_COLORS[i];

                EditorMode currentMode = m_app.GetCurrentMode();

                // В режиме Select устанавливаем только цвет по умолчанию
                if (currentMode == EditorMode::Select)
                {
                    m_app.SetOutlineColor(selectedColor);
                }
                // В режиме Fill меняем цвет заливки выделенных фигур
                else if (currentMode == EditorMode::Fill)
                {
                    auto& selected = m_app.GetSelected();
                    if (!selected.empty())
                    {
                        std::vector<std::shared_ptr<IGeometry>> shapesToChange;
                        shapesToChange.reserve(selected.size());

                        for (auto& shape : selected)
                        {
                            shapesToChange.push_back(shape);
                        }

                        auto cmd = std::make_unique<ChangeStyleCommand>(
                            std::move(shapesToChange),
                            selected[0]->GetFillColor(),
                            selectedColor,
                            selected[0]->GetOutlineColor(),
                            selected[0]->GetOutlineColor(),
                            selected[0]->GetOutlineThickness(),
                            selected[0]->GetOutlineThickness()
                        );

                        m_app.ExecuteCommand(std::move(cmd));
                    }
                    m_app.SetFillColor(selectedColor);
                }
                // В режимах добавления фигур меняем цвет контура для будущих фигур
                else if (currentMode == EditorMode::AddTriangle ||
                    currentMode == EditorMode::AddRectangle ||
                    currentMode == EditorMode::AddCircle)
                {
                    m_app.SetOutlineColor(selectedColor);
                }

                return 1; // Клик обработан
            }
        }

        // Проверка кнопок толщины
        for (size_t i = 0; i < m_thicknessButtons.size(); ++i)
        {
            const auto& btn = m_thicknessButtons[i];
            const auto btnPos = btn.getPosition();
            const auto btnSize = btn.getSize();

            if (pos.x >= btnPos.x && pos.x <= btnPos.x + btnSize.x &&
                pos.y >= btnPos.y && pos.y <= btnPos.y + btnSize.y)
            {
                m_selectedThicknessIndex = static_cast<int>(i);
                float thickness = Constants::AVAILABLE_THICKNESSES[i];

                // Применяем толщину только в режимах, где это имеет смысл
                EditorMode currentMode = m_app.GetCurrentMode();

                if (currentMode != EditorMode::Select) // В Select не меняем толщину
                {
                    // Применение толщины с возможностью отмены
                    auto& selected = m_app.GetSelected();
                    if (!selected.empty())
                    {
                        std::vector<std::shared_ptr<IGeometry>> shapesToChange;
                        shapesToChange.reserve(selected.size());

                        for (auto& shape : selected)
                        {
                            shapesToChange.push_back(shape);
                        }

                        auto cmd = std::make_unique<ChangeStyleCommand>(
                            std::move(shapesToChange),
                            selected[0]->GetFillColor(),
                            selected[0]->GetFillColor(),
                            selected[0]->GetOutlineColor(),
                            selected[0]->GetOutlineColor(),
                            selected[0]->GetOutlineThickness(),
                            thickness
                        );

                        m_app.ExecuteCommand(std::move(cmd));
                    }
                }

                m_app.SetOutlineThickness(thickness);
                return 1; // Клик обработан
            }
        }

        return 0; // Клик не обработан (не попал в кнопки)
    }

    // Возвращает границы панели инструментов
    sf::FloatRect Toolbar::GetBounds() const
    {
        return sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1000.0f, Constants::TOOLBAR_HEIGHT));
    }

}