#ifndef GEOM_VISUALIZER_GEOMETRY_H
#define GEOM_VISUALIZER_GEOMETRY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace geom 
{
struct Point 
{
  int x;
  int y;
};

class IGeometry 
{
public:
  virtual ~IGeometry() = default;
  virtual double getPerimeter() const = 0;
  virtual double getArea() const = 0;
  virtual void draw(sf::RenderTarget& target) const = 0;
  virtual std::string toOutputString() const = 0;
};

double distance(const Point& a, const Point& b);

constexpr double PI() 
{
	return 3.14159265358979323846; 
}

}

#endif  