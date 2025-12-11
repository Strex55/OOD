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

        void Draw(sf::RenderTarget& target);
        void HandleClick(const sf::Vector2f& pos);
        sf::FloatRect GetBounds() const;

    private:
        void LoadFont();
        void InitializeToolButtons();
        void InitializeColorButtons();
        void InitializeThicknessButtons();

        Application& m_app;  // Reference to Application (Facade)

        // SFML elements
        sf::RectangleShape m_background;
        std::vector<sf::RectangleShape> m_toolButtons;
        std::vector<sf::RectangleShape> m_colorButtons;
        std::vector<sf::RectangleShape> m_thicknessButtons;
        std::vector<sf::Text> m_toolLabels;
        std::vector<sf::Text> m_thicknessLabels;
        sf::Font m_font;

        // Current selections
        int m_selectedToolIndex = 0;      // State Pattern: current tool/mode
        int m_selectedColorIndex = 0;     // Currently selected color
        int m_selectedThicknessIndex = 0; // Currently selected thickness
    };

}
#endif 