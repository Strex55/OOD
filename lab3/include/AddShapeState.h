#ifndef GEOM_VISUALIZER_ADD_SHAPE_STATE_H
#define GEOM_VISUALIZER_ADD_SHAPE_STATE_H

#include "EditorState.h"

namespace geom
{

    class Application;

    class AddShapeState : public IEditorState
    {
    public:
        AddShapeState(Application& app, EditorMode mode);
        void OnMousePress(const sf::Vector2f& pos) override;
        void OnMouseMove(const sf::Vector2f& pos) override;
        void OnMouseRelease(const sf::Vector2f& pos) override;
        EditorMode GetMode() const override
        {
            return mode_;
        }

    private:
        Application& app_;
        EditorMode mode_;
        bool firstClick_;
        bool secondClick_;       
        bool circleCenterSet_;   

        struct LocalPoint { int x, y; } p1_, p2_, p3_, center_; 
        int radius_; 
    };

}

#endif