#ifndef GEOM_VISUALIZER_SHAPE_ADAPTER_H
#define GEOM_VISUALIZER_SHAPE_ADAPTER_H

#include "Geometry.h"           
#include <SFML/Graphics.hpp>
#include <memory>

namespace geom
{

    class ShapeAdapter : public IGeometry
    {
    public:
        ~ShapeAdapter() override = default;

        // IGeometry interface implementation
        void Draw(sf::RenderTarget& target) const override;
        sf::FloatRect GetBounds() const override;
        void MoveBy(float dx, float dy) override;

        // Style setters
        void SetFillColor(const sf::Color& color) override;
        void SetOutlineColor(const sf::Color& color) override;
        void SetOutlineThickness(float thickness) override;

        // Style getters
        sf::Color GetFillColor() const override;
        sf::Color GetOutlineColor() const override;
        float GetOutlineThickness() const override;

    protected:
        // Protected constructor for derived classes
        explicit ShapeAdapter(std::unique_ptr<sf::Shape> shape);

        // Helper method to set style
        void SetStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness);

        // Access to wrapped SFML shape
        const sf::Shape& GetShape() const { return *m_shape; }
        sf::Shape& GetShape() { return *m_shape; }

    private:
        std::unique_ptr<sf::Shape> m_shape;
    };

} 

#endif 