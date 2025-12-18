#include "ShapeAdapter.h"

namespace geom {

    ShapeAdapter::ShapeAdapter(std::unique_ptr<sf::Shape> shape)
        : m_shape(std::move(shape))
    {
    }

    void ShapeAdapter::Draw(sf::RenderTarget& target) const
    {
        target.draw(*m_shape);  
    }

    sf::FloatRect ShapeAdapter::GetBounds() const
    {
        return m_shape->getGlobalBounds();  
    }

    void ShapeAdapter::MoveBy(float dx, float dy)
    {
        m_shape->move(sf::Vector2f(dx, dy));  
    }

    void ShapeAdapter::SetFillColor(const sf::Color& color)
    {
        m_shape->setFillColor(color);  
    }

    void ShapeAdapter::SetOutlineColor(const sf::Color& color)
    {
        m_shape->setOutlineColor(color);  
    }

    void ShapeAdapter::SetOutlineThickness(float thickness)
    {
        m_shape->setOutlineThickness(thickness);  
    }

    sf::Color ShapeAdapter::GetFillColor() const
    {
        return m_shape->getFillColor();  
    }

    sf::Color ShapeAdapter::GetOutlineColor() const
    {
        return m_shape->getOutlineColor();  
    }

    float ShapeAdapter::GetOutlineThickness() const
    {
        return m_shape->getOutlineThickness();  
    }

    void ShapeAdapter::SetStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness)
    {
        m_shape->setFillColor(fill);
        m_shape->setOutlineColor(outline);
        m_shape->setOutlineThickness(outlineThickness);
    }

} 