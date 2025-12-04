#ifndef GEOM_VISUALIZER_CIRCLE_Adapter_H
#define GEOM_VISUALIZER_CIRCLE_Adapter_H

#include "ShapeAdapter.h"

namespace geom 
{
class CircleAdapter : public ShapeAdapter 
{
public:
  CircleAdapter(const Point& center, int radius);
  ~CircleAdapter() override = default;

  double getPerimeter() const override;
  double getArea() const override;
  std::string toOutputString() const override;

private:
  Point center_;
  int radius_;
};

}

#endif  