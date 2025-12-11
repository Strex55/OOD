#ifndef GEOM_VISUALIZER_ADD_SHAPE_STATE_H
#define GEOM_VISUALIZER_ADD_SHAPE_STATE_H

#include "EditorState.h"

namespace geom {

class Application;

class AddShapeState : public IEditorState {
public:
  AddShapeState(Application& app, EditorMode mode);
  void onMousePress(const sf::Vector2f& pos) override;
  void onMouseMove(const sf::Vector2f& pos) override;
  void onMouseRelease(const sf::Vector2f& pos) override;
  EditorMode getMode() const override { return mode_; }

private:
  Application& app_;
  EditorMode mode_;
  bool firstClick_;
  bool secondClick_;  // For triangle (need 3 points)
  bool circleCenterSet_;  // For circle (need center then radius)
  struct LocalPoint { int x, y; } p1_, p2_, p3_, center_;
  int radius_;
};

}

#endif 