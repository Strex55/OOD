#ifndef GEOM_VISUALIZER_GEOMETRY_HPP
#define GEOM_VISUALIZER_GEOMETRY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace geom {

struct Point {
  int x;
  int y;
};

class IGeometry {
public:
  virtual ~IGeometry() = default;
  virtual double getPerimeter() const = 0;
  virtual double getArea() const = 0;
  virtual void draw(sf::RenderTarget& target) const = 0;
  virtual std::string toOutputString() const = 0;
  // New interaction methods
  virtual bool containsPoint(const sf::Vector2f& point) const = 0;
  virtual sf::FloatRect getBounds() const = 0;
  virtual void moveBy(float dx, float dy) = 0;
};

double distance(const Point& a, const Point& b);

constexpr double PI() { return 3.14159265358979323846; }

}

#endif