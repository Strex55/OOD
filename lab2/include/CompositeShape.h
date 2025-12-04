#ifndef GEOM_VISUALIZER_COMPOSITE_SHAPE_HPP
#define GEOM_VISUALIZER_COMPOSITE_SHAPE_HPP

#include "Geometry.h"
#include <memory>
#include <vector>

namespace geom {

class CompositeShape : public IGeometry {
public:
  CompositeShape() = default;

  void add(const std::shared_ptr<IGeometry>& child);
  void remove(const std::shared_ptr<IGeometry>& child);
  const std::vector<std::shared_ptr<IGeometry>>& children() const { return children_; }

  double getPerimeter() const override;
  double getArea() const override;
  void draw(sf::RenderTarget& target) const override;
  std::string toOutputString() const override;
  bool containsPoint(const sf::Vector2f& point) const override;
  sf::FloatRect getBounds() const override;
  void moveBy(float dx, float dy) override;

private:
  std::vector<std::shared_ptr<IGeometry>> children_;
};

}

#endif