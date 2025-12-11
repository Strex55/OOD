#include "TriangleAdapter.h"
#include <sstream>
#include <cmath>

namespace geom {

static std::unique_ptr<sf::ConvexShape> makeTriangleShape(const Point& p1, const Point& p2, const Point& p3) {
  auto shape = std::make_unique<sf::ConvexShape>(3);
  shape->setPoint(0, sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y)));
  shape->setPoint(1, sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y)));
  shape->setPoint(2, sf::Vector2f(static_cast<float>(p3.x), static_cast<float>(p3.y)));
  shape->setFillColor(sf::Color(200, 200, 255));
  shape->setOutlineColor(sf::Color::Blue);
  shape->setOutlineThickness(1.0f);
  return shape;
}

TriangleAdapter::TriangleAdapter(const Point& p1, const Point& p2, const Point& p3)
  : ShapeAdapter(makeTriangleShape(p1, p2, p3)), p1_(p1), p2_(p2), p3_(p3) {}

double TriangleAdapter::getPerimeter() const {
  return distance(p1_, p2_) + distance(p2_, p3_) + distance(p3_, p1_);
}

double TriangleAdapter::getArea() const {
  // Shoelace formula for triangle
  const double area = std::abs(
    static_cast<double>(p1_.x) * (p2_.y - p3_.y) +
    static_cast<double>(p2_.x) * (p3_.y - p1_.y) +
    static_cast<double>(p3_.x) * (p1_.y - p2_.y)
  ) / 2.0;
  return area;
}

std::string TriangleAdapter::toOutputString() const {
  std::ostringstream oss;
  oss << "TRIANGLE: P=" << static_cast<long long>(std::llround(getPerimeter()))
      << "; S=" << static_cast<long long>(std::llround(getArea()));
  return oss.str();
}

static float cross(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool TriangleAdapter::containsPoint(const sf::Vector2f& point) const {
  // Barycentric via sign of cross products
  sf::Vector2f a(static_cast<float>(p1_.x), static_cast<float>(p1_.y));
  sf::Vector2f b(static_cast<float>(p2_.x), static_cast<float>(p2_.y));
  sf::Vector2f c(static_cast<float>(p3_.x), static_cast<float>(p3_.y));
  bool b1 = cross(point, a, b) < 0.0f;
  bool b2 = cross(point, b, c) < 0.0f;
  bool b3 = cross(point, c, a) < 0.0f;
  return (b1 == b2) && (b2 == b3);
}

void TriangleAdapter::setFillColor(const sf::Color& color) {
    shape().setFillColor(color);
}

void TriangleAdapter::setOutlineColor(const sf::Color& color) {
    shape().setOutlineColor(color);
}

void TriangleAdapter::setOutlineThickness(float thickness) {
    shape().setOutlineThickness(thickness);
}

void TriangleAdapter::moveBy(float dx, float dy) {
  ShapeAdapter::moveBy(dx, dy);
  p1_.x += static_cast<int>(std::lround(dx));
  p1_.y += static_cast<int>(std::lround(dy));
  p2_.x += static_cast<int>(std::lround(dx));
  p2_.y += static_cast<int>(std::lround(dy));
  p3_.x += static_cast<int>(std::lround(dx));
  p3_.y += static_cast<int>(std::lround(dy));
}

} 