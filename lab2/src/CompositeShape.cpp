#include "CompositeShape.h"
#include <algorithm>
#include <sstream>

namespace geom {

void CompositeShape::add(const std::shared_ptr<IGeometry>& child) {
  children_.push_back(child);
}

void CompositeShape::remove(const std::shared_ptr<IGeometry>& child) {
  children_.erase(std::remove(children_.begin(), children_.end(), child), children_.end());
}

double CompositeShape::getPerimeter() const {
  double p = 0.0;
  for (const auto& c : children_) p += c->getPerimeter();
  return p;
}

double CompositeShape::getArea() const {
  double s = 0.0;
  for (const auto& c : children_) s += c->getArea();
  return s;
}

void CompositeShape::draw(sf::RenderTarget& target) const {
  for (const auto& c : children_) c->draw(target);
}

std::string CompositeShape::toOutputString() const {
  std::ostringstream oss;
  oss << "GROUP: P=" << static_cast<long long>(std::llround(getPerimeter()))
      << "; S=" << static_cast<long long>(std::llround(getArea()));
  return oss.str();
}

bool CompositeShape::containsPoint(const sf::Vector2f& point) const {
  for (const auto& c : children_) {
    if (c->containsPoint(point)) return true;
  }
  return false;
}

sf::FloatRect CompositeShape::getBounds() const {
  if (children_.empty()) return sf::FloatRect();
  auto b = children_.front()->getBounds();
  float left = b.position.x;
  float top = b.position.y;
  float right = b.position.x + b.size.x;
  float bottom = b.position.y + b.size.y;
  for (size_t i = 1; i < children_.size(); ++i) {
    auto bi = children_[i]->getBounds();
    left = std::min(left, bi.position.x);
    top = std::min(top, bi.position.y);
    right = std::max(right, bi.position.x + bi.size.x);
    bottom = std::max(bottom, bi.position.y + bi.size.y);
  }
  return sf::FloatRect(sf::Vector2f(left, top), sf::Vector2f(right - left, bottom - top));
}

void CompositeShape::moveBy(float dx, float dy) {
  for (const auto& c : children_) c->moveBy(dx, dy);
}

}  