#include "SelectState.h"
#include "Application.h"
#include "Geometry.h"
#include <algorithm>

namespace geom {

SelectState::SelectState(Application& app) : app_(app) {}

void SelectState::onMousePress(const sf::Vector2f& pos) {
    std::shared_ptr<IGeometry> hit = nullptr;
    auto& shapes = app_.getShapes();
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
      if ((*it)->containsPoint(pos)) {
        hit = *it;
        break;
      }
    }

    const bool addToSelection = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift)
                             || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift);
    if (!addToSelection) {
      app_.clearSelection();
    }

    if (hit) {
      auto& selected = app_.getSelected();
      auto found = std::find(selected.begin(), selected.end(), hit);
      if (addToSelection && found != selected.end()) {
        selected.erase(found);
      } else {
        app_.selectShape(hit, addToSelection);
      }
    }
  }

void SelectState::onMouseMove(const sf::Vector2f& pos) {
  auto& selected = app_.getSelected();
  if (!selected.empty()) {
  }
}

void SelectState::onMouseRelease(const sf::Vector2f& pos) {
}

}