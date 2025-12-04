#ifndef GEOM_VISUALIZER_SHAPE_Adapter_H
#define GEOM_VISUALIZER_SHAPE_Adapter_H

#include "Geometry.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace geom {

class ShapeAdapter : public IGeometry {
public:
  ~ShapeAdapter() override = default;

  void draw(sf::RenderTarget& target) const override;

protected:
  explicit ShapeAdapter(std::unique_ptr<sf::Shape> shape);

  void setStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness);

  std::unique_ptr<sf::Shape> shape_;
};

}

#endif  