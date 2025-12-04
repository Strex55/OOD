#include "CircleAdapter.h"
#include <sstream>

namespace geom {

static std::unique_ptr<sf::CircleShape> makeCircleShape(const Point& center, int radius) {
  auto shape = std::make_unique<sf::CircleShape>(static_cast<float>(radius));
  shape->setOrigin(sf::Vector2f(static_cast<float>(radius), static_cast<float>(radius)));
  shape->setPosition(sf::Vector2f(static_cast<float>(center.x), static_cast<float>(center.y)));
  shape->setFillColor(sf::Color(255, 220, 220));
  shape->setOutlineColor(sf::Color::Red);
  shape->setOutlineThickness(1.0f);
  return shape;
}

CircleAdapter::CircleAdapter(const Point& center, int radius)
  : ShapeAdapter(makeCircleShape(center, radius)), center_(center), radius_(radius) {}

double CircleAdapter::getPerimeter() const {
  return 2.0 * PI() * static_cast<double>(radius_);
}

double CircleAdapter::getArea() const {
  return PI() * static_cast<double>(radius_) * static_cast<double>(radius_);
}

std::string CircleAdapter::toOutputString() const {
  std::ostringstream oss;
  oss << "CIRCLE: P=" << static_cast<long long>(std::llround(getPerimeter()))
      << "; S=" << static_cast<long long>(std::llround(getArea()));
  return oss.str();
}

}  