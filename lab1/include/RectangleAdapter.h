#ifndef GEOM_VISUALIZER_RECTANGLE_Adapter_H
#define GEOM_VISUALIZER_RECTANGLE_Adapter_H

#include "ShapeAdapter.h"

namespace geom {

class RectangleAdapter : public ShapeAdapter {
public:
  RectangleAdapter(const Point& p1, const Point& p2);
  ~RectangleAdapter() override = default;

  double getPerimeter() const override;
  double getArea() const override;
  std::string toOutputString() const override;

private:
  Point p1_;
  Point p2_;
  int width_;
  int height_;
};

}

#endif  