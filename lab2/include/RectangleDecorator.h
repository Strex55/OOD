#ifndef GEOM_VISUALIZER_RECTANGLE_DECORATOR_HPP
#define GEOM_VISUALIZER_RECTANGLE_DECORATOR_HPP

#include "ShapeDecorator.h"

namespace geom {

class RectangleDecorator : public ShapeDecorator {
public:
  RectangleDecorator(const Point& p1, const Point& p2);
  ~RectangleDecorator() override = default;

  double getPerimeter() const override;
  double getArea() const override;
  std::string toOutputString() const override;
  bool containsPoint(const sf::Vector2f& point) const override;
  void moveBy(float dx, float dy) override;

private:
  Point p1_;
  Point p2_;
  int width_;
  int height_;
};

}

#endif