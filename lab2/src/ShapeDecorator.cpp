#include "ShapeDecorator.h"

namespace geom {

ShapeDecorator::ShapeDecorator(std::unique_ptr<sf::Shape> shape)
  : shape_(std::move(shape)) {
}

void ShapeDecorator::setStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness) {
  shape_->setFillColor(fill);
  shape_->setOutlineColor(outline);
  shape_->setOutlineThickness(outlineThickness);
}

void ShapeDecorator::draw(sf::RenderTarget& target) const {
  target.draw(*shape_);
}

sf::FloatRect ShapeDecorator::getBounds() const {
  return shape_->getGlobalBounds();
}

void ShapeDecorator::moveBy(float dx, float dy) {
  shape_->move(sf::Vector2f(dx, dy));
}

}