#include "RectangleDecorator.h"
#include <algorithm>
#include <sstream>

namespace geom {

static std::unique_ptr<sf::RectangleShape> makeRectShape(const Point& p1, const Point& p2, int& outW, int& outH) {
  const int left = std::min(p1.x, p2.x);
  const int top = std::min(p1.y, p2.y);
  const int right = std::max(p1.x, p2.x);
  const int bottom = std::max(p1.y, p2.y);
  outW = right - left;
  outH = bottom - top;
  auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(static_cast<float>(outW), static_cast<float>(outH)));
  shape->setPosition(sf::Vector2f(static_cast<float>(left), static_cast<float>(top)));
  shape->setFillColor(sf::Color(200, 255, 200));
  shape->setOutlineColor(sf::Color::Green);
  shape->setOutlineThickness(1.0f);
  return shape;
}

RectangleDecorator::RectangleDecorator(const Point& p1, const Point& p2)
  : ShapeDecorator(makeRectShape(p1, p2, width_, height_)), p1_(p1), p2_(p2) {}

double RectangleDecorator::getPerimeter() const {
  return 2.0 * (static_cast<double>(width_) + static_cast<double>(height_));
}

double RectangleDecorator::getArea() const {
  return static_cast<double>(width_) * static_cast<double>(height_);
}

std::string RectangleDecorator::toOutputString() const {
  std::ostringstream oss;
  oss << "RECTANGLE: P=" << static_cast<long long>(std::llround(getPerimeter()))
      << "; S=" << static_cast<long long>(std::llround(getArea()));
  return oss.str();
}

bool RectangleDecorator::containsPoint(const sf::Vector2f& point) const {
  return getBounds().contains(point);
}

void RectangleDecorator::moveBy(float dx, float dy) {
  ShapeDecorator::moveBy(dx, dy);
  p1_.x += static_cast<int>(std::lround(dx));
  p1_.y += static_cast<int>(std::lround(dy));
  p2_.x += static_cast<int>(std::lround(dx));
  p2_.y += static_cast<int>(std::lround(dy));
}

} 