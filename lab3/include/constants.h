#ifndef GEOM_VISUALIZER_CONSTANTS_H
#define GEOM_VISUALIZER_CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace geom
{

    namespace Constants
    {
        // Окно приложения
        constexpr unsigned int WINDOW_WIDTH = 1000;
        constexpr unsigned int WINDOW_HEIGHT = 700;
        constexpr char WINDOW_TITLE[] = "Geometry Editor";
        constexpr unsigned int FRAME_RATE_LIMIT = 60;

        // Панель инструментов (использование State Pattern)
        constexpr float TOOLBAR_HEIGHT = 80.0f;
        constexpr float BUTTON_SIZE = 50.0f;
        constexpr float BUTTON_SPACING = 5.0f;

        // Доступные цвета для панели инструментов (3-5 цветов как требуется)
        const std::vector<sf::Color> AVAILABLE_COLORS = {
            sf::Color::Black,
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color(255, 165, 0)  // Оранжевый
        };

        // Доступные толщины для панели инструментов (2-3 толщины как требуется)
        const std::vector<float> AVAILABLE_THICKNESSES = { 1.0f, 2.0f, 3.0f };

        // Названия инструментов для кнопок панели инструментов
        const std::vector<std::string> TOOL_NAMES = {
            "Select",     // Режим выделения + перетаскивания
            "Fill",       // Режим заливки цветом
            "Triangle",   // Добавление треугольника
            "Rectangle",  // Добавление прямоугольника
            "Circle"      // Добавление круга
        };

        // Цвета
        const sf::Color BACKGROUND_COLOR = sf::Color::White;
        const sf::Color SELECTION_COLOR = sf::Color(0, 120, 255);
        const sf::Color TOOLBAR_BACKGROUND = sf::Color(240, 240, 240);
        const sf::Color TOOLBAR_OUTLINE = sf::Color(200, 200, 200);
        const sf::Color BUTTON_DEFAULT_COLOR = sf::Color(220, 220, 220);
        const sf::Color BUTTON_SELECTED_COLOR = sf::Color(180, 220, 255);

        // Геометрия
        constexpr double PI = 3.14159265358979323846;
        constexpr float SELECTION_OUTLINE_THICKNESS = 1.5f;
        constexpr float MIN_DRAG_THRESHOLD = 0.01f;
    }

} 

#endif 