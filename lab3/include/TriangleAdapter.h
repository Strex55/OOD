#ifndef GEOM_VISUALIZER_TRIANGLE_ADAPTER_H
#define GEOM_VISUALIZER_TRIANGLE_ADAPTER_H

#include "ShapeAdapter.h"

namespace geom {

class TriangleAdapter : public ShapeAdapter {
public:
  TriangleAdapter(const Point& p1, const Point& p2, const Point& p3);
  ~TriangleAdapter() override = default;

  double getPerimeter() const override;
  double getArea() const override;
  std::string toOutputString() const override;
  bool containsPoint(const sf::Vector2f& point) const override;
  void moveBy(float dx, float dy) override;
  void setFillColor(const sf::Color& color) override;
  void setOutlineColor(const sf::Color& color) override;
  void setOutlineThickness(float thickness) override;

private:
  Point p1_;
  Point p2_;
  Point p3_;
};

}  

#endif