#ifndef GEOM_VISUALIZER_CIRCLE_DECORATOR_HPP
#define GEOM_VISUALIZER_CIRCLE_DECORATOR_HPP

#include "ShapeDecorator.h"

namespace geom {

class CircleDecorator : public ShapeDecorator {
public:
  CircleDecorator(const Point& center, int radius);
  ~CircleDecorator() override = default;

  double getPerimeter() const override;
  double getArea() const override;
  std::string toOutputString() const override;
  bool containsPoint(const sf::Vector2f& point) const override;
  void moveBy(float dx, float dy) override;

private:
  Point center_;
  int radius_;
};

}

#endif