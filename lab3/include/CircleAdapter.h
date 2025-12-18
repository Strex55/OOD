#ifndef GEOM_VISUALIZER_CIRCLE_ADAPTER_H
#define GEOM_VISUALIZER_CIRCLE_ADAPTER_H

#include "ShapeAdapter.h"

namespace geom
{

    class CircleAdapter : public ShapeAdapter
    {
    public:
        CircleAdapter(const Point& center, int radius);
        ~CircleAdapter() override = default;

        double GetPerimeter() const override;
        double GetArea() const override;
        std::string ToOutputString() const override;
        bool ContainsPoint(const sf::Vector2f& point) const override;
        void MoveBy(float dx, float dy) override;
        void SetFillColor(const sf::Color& color) override;
        void SetOutlineColor(const sf::Color& color) override;
        void SetOutlineThickness(float thickness) override;

    private:
        Point center_;
        int radius_;
    };

} 

#endif 