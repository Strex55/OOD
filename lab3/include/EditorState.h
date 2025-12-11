#ifndef GEOM_VISUALIZER_EDITOR_STATE_H
#define GEOM_VISUALIZER_EDITOR_STATE_H

#include <SFML/Graphics.hpp>

namespace geom {

enum class EditorMode {
  Select,    // Drag-and-drop mode
  Fill,      // Fill color mode
  AddTriangle,
  AddRectangle,
  AddCircle
};

class IEditorState {
public:
  virtual ~IEditorState() = default;
  virtual void onMousePress(const sf::Vector2f& pos) = 0;
  virtual void onMouseMove(const sf::Vector2f& pos) = 0;
  virtual void onMouseRelease(const sf::Vector2f& pos) = 0;
  virtual EditorMode getMode() const = 0;
};

}

#endif