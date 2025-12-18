#ifndef GEOM_VISUALIZER_COMPOSITE_SHAPE_H
#define GEOM_VISUALIZER_COMPOSITE_SHAPE_H

#include "Geometry.h"
#include <memory>
#include <vector>

namespace geom
{

    class CompositeShape : public IGeometry
    {
    public:
        CompositeShape() = default;

        // Операции композита
        void Add(const std::shared_ptr<IGeometry>& child);
        void Remove(const std::shared_ptr<IGeometry>& child);
        const std::vector<std::shared_ptr<IGeometry>>& GetChildren() const { return m_children; }

        // Реализация интерфейса IGeometry
        double GetPerimeter() const override;
        double GetArea() const override;
        void Draw(sf::RenderTarget& target) const override;
        std::string ToOutputString() const override;
        bool ContainsPoint(const sf::Vector2f& point) const override;
        sf::FloatRect GetBounds() const override;
        void MoveBy(float dx, float dy) override;

        // Установка стилей
        void SetFillColor(const sf::Color& color) override;
        void SetOutlineColor(const sf::Color& color) override;
        void SetOutlineThickness(float thickness) override;

        // Получение стилей
        sf::Color GetFillColor() const override;
        sf::Color GetOutlineColor() const override;
        float GetOutlineThickness() const override;

    private:
        std::vector<std::shared_ptr<IGeometry>> m_children;
    };

} 

#endif 