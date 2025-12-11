#ifndef GEOM_VISUALIZER_FILL_STATE_H
#define GEOM_VISUALIZER_FILL_STATE_H

#include "EditorState.h"

namespace geom {

class Application;

class FillState : public IEditorState {
public:
  explicit FillState(Application& app);
  void onMousePress(const sf::Vector2f& pos) override;
  void onMouseMove(const sf::Vector2f& pos) override;
  void onMouseRelease(const sf::Vector2f& pos) override;
  EditorMode getMode() const override { return EditorMode::Fill; }

private:
  Application& app_;
};

}

#endif