#ifndef GEOM_VISUALIZER_SHAPE_DECORATOR_HPP
#define GEOM_VISUALIZER_SHAPE_DECORATOR_HPP

#include "Geometry.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace geom {

class ShapeDecorator : public IGeometry {
public:
  ~ShapeDecorator() override = default;

  void draw(sf::RenderTarget& target) const override;
  sf::FloatRect getBounds() const override;
  void moveBy(float dx, float dy) override;

protected:
  explicit ShapeDecorator(std::unique_ptr<sf::Shape> shape);

  void setStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness);

  const sf::Shape& shape() const { return *shape_; }
  sf::Shape& shape() { return *shape_; }

  std::unique_ptr<sf::Shape> shape_;
};

}

#endif