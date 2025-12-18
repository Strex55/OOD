#ifndef GEOM_VISUALIZER_GEOMETRY_H
#define GEOM_VISUALIZER_GEOMETRY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace geom
{

    struct Point
    {
        int x;
        int y;
    };

    class IGeometry
    {
    public:
        virtual ~IGeometry() = default;

        // Геометрические вычисления
        virtual double GetPerimeter() const = 0;
        virtual double GetArea() const = 0;

        // Отрисовка
        virtual void Draw(sf::RenderTarget& target) const = 0;

        // Сериализация
        virtual std::string ToOutputString() const = 0;

        // Взаимодействие
        virtual bool ContainsPoint(const sf::Vector2f& point) const = 0;
        virtual sf::FloatRect GetBounds() const = 0;
        virtual void MoveBy(float dx, float dy) = 0;

        // Установка стилей (из лабораторной работы 3)
        virtual void SetFillColor(const sf::Color& color) = 0;
        virtual void SetOutlineColor(const sf::Color& color) = 0;
        virtual void SetOutlineThickness(float thickness) = 0;

        // Получение стилей - необходимо для отмены действий
        virtual sf::Color GetFillColor() const = 0;
        virtual sf::Color GetOutlineColor() const = 0;
        virtual float GetOutlineThickness() const = 0;
    };

    // Вспомогательные функции
    double Distance(const Point& a, const Point& b);
    constexpr double PI() { return 3.14159265358979323846; }

} 

#endif 