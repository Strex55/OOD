#include "Geometry.h"
#include <cmath>

namespace geom {

double distance(const Point& a, const Point& b) {
  const double dx = static_cast<double>(a.x - b.x);
  const double dy = static_cast<double>(a.y - b.y);
  return std::sqrt(dx * dx + dy * dy);
}

}