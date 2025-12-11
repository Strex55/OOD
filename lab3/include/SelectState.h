#ifndef GEOM_VISUALIZER_SELECT_STATE_H
#define GEOM_VISUALIZER_SELECT_STATE_H

#include "EditorState.h"

namespace geom {

class Application;

class SelectState : public IEditorState {
public:
  explicit SelectState(Application& app);
  void onMousePress(const sf::Vector2f& pos) override;
  void onMouseMove(const sf::Vector2f& pos) override;
  void onMouseRelease(const sf::Vector2f& pos) override;
  EditorMode getMode() const override { return EditorMode::Select; }

private:
  Application& app_;
};

}

#endif