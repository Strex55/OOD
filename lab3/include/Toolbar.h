#ifndef GEOM_VISUALIZER_TOOLBAR_H
#define GEOM_VISUALIZER_TOOLBAR_H

#include "EditorState.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace geom
{

    class Application;

    class Toolbar
    {
    public:
        explicit Toolbar(Application& app);

        int Draw(sf::RenderTarget& target);
        int HandleClick(const sf::Vector2f& pos);
        sf::FloatRect GetBounds() const;

    private:
        int LoadFont();
        void InitializeToolButtons();
        void InitializeColorButtons();
        void InitializeThicknessButtons();

        Application& m_app; // Ссылка на Application (Facade)

        // SFML элементы
        sf::RectangleShape m_background;
        std::vector<sf::RectangleShape> m_toolButtons;
        std::vector<sf::RectangleShape> m_colorButtons;
        std::vector<sf::RectangleShape> m_thicknessButtons;
        std::vector<sf::Text> m_toolLabels;
        std::vector<sf::Text> m_thicknessLabels;
        sf::Font m_font;

        // Текущие выделения
        int m_selectedToolIndex = 0;      // State Pattern: текущий инструмент/режим
        int m_selectedColorIndex = 0;     // Текущий выбранный цвет
        int m_selectedThicknessIndex = 0; // Текущая выбранная толщина
    };

} 

#endif 