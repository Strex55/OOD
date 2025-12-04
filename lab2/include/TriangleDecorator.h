#ifndef GEOM_VISUALIZER_TRIANGLE_DECORATOR_HPP
#define GEOM_VISUALIZER_TRIANGLE_DECORATOR_HPP

#include "ShapeDecorator.h"

namespace geom {

class TriangleDecorator : public ShapeDecorator {
public:
  TriangleDecorator(const Point& p1, const Point& p2, const Point& p3);
  ~TriangleDecorator() override = default;

  double getPerimeter() const override;
  double getArea() const override;
  std::string toOutputString() const override;
  bool containsPoint(const sf::Vector2f& point) const override;
  void moveBy(float dx, float dy) override;

private:
  Point p1_;
  Point p2_;
  Point p3_;
};

}

#endif