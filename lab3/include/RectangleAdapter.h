#ifndef GEOM_VISUALIZER_RECTANGLE_ADAPTER_H
#define GEOM_VISUALIZER_RECTANGLE_ADAPTER_H

#include "ShapeAdapter.h"

namespace geom
{

    class RectangleAdapter : public ShapeAdapter
    {
    public:
        RectangleAdapter(const Point& p1, const Point& p2);
        ~RectangleAdapter() override = default;

        double GetPerimeter() const override;
        double GetArea() const override;
        std::string ToOutputString() const override;
        bool ContainsPoint(const sf::Vector2f& point) const override;
        void MoveBy(float dx, float dy) override;
        void SetFillColor(const sf::Color& color) override;
        void SetOutlineColor(const sf::Color& color) override;
        void SetOutlineThickness(float thickness) override;

    private:
        Point p1_;
        Point p2_;
        int width_;
        int height_;
    };

} 

#endif 