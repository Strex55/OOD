#include "CircleAdapter.h"
#include <sstream>

namespace geom
{

    static std::unique_ptr<sf::CircleShape> MakeCircleShape(const Point& center, int radius)
    {
        auto shape = std::make_unique<sf::CircleShape>(static_cast<float>(radius));
        shape->setOrigin(sf::Vector2f(static_cast<float>(radius), static_cast<float>(radius)));
        shape->setPosition(sf::Vector2f(static_cast<float>(center.x), static_cast<float>(center.y)));
        shape->setFillColor(sf::Color(255, 220, 220));
        shape->setOutlineColor(sf::Color::Red);
        shape->setOutlineThickness(1.0f);
        return shape;
    }

    CircleAdapter::CircleAdapter(const Point& center, int radius)
        : ShapeAdapter(MakeCircleShape(center, radius)), center_(center), radius_(radius)
    {
    }

    double CircleAdapter::GetPerimeter() const
    {
        return 2.0 * PI() * static_cast<double>(radius_);
    }

    double CircleAdapter::GetArea() const
    {
        return PI() * static_cast<double>(radius_) * static_cast<double>(radius_);
    }

    std::string CircleAdapter::ToOutputString() const
    {
        std::ostringstream oss;
        oss << "CIRCLE: P=" << static_cast<long long>(std::llround(GetPerimeter()))
            << "; S=" << static_cast<long long>(std::llround(GetArea()));
        return oss.str();
    }

    bool CircleAdapter::ContainsPoint(const sf::Vector2f& point) const
    {
        const float dx = point.x - static_cast<float>(center_.x);
        const float dy = point.y - static_cast<float>(center_.y);
        return (dx * dx + dy * dy) <= static_cast<float>(radius_ * radius_);
    }

    void CircleAdapter::SetFillColor(const sf::Color& color)
    {
        GetShape().setFillColor(color);
    }

    void CircleAdapter::SetOutlineColor(const sf::Color& color)
    {
        GetShape().setOutlineColor(color);
    }

    void CircleAdapter::SetOutlineThickness(float thickness)
    {
        GetShape().setOutlineThickness(thickness);
    }

    void CircleAdapter::MoveBy(float dx, float dy)
    {
        ShapeAdapter::MoveBy(dx, dy);
        center_.x += static_cast<int>(std::lround(dx));
        center_.y += static_cast<int>(std::lround(dy));
    }

}