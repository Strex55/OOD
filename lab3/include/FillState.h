#ifndef GEOM_VISUALIZER_FILL_STATE_H
#define GEOM_VISUALIZER_FILL_STATE_H

#include "EditorState.h"

namespace geom
{

    class Application;

    class FillState : public IEditorState
    {
    public:
        explicit FillState(Application& app);
        void OnMousePress(const sf::Vector2f& pos) override;
        void OnMouseMove(const sf::Vector2f& pos) override;
        void OnMouseRelease(const sf::Vector2f& pos) override;
        EditorMode GetMode() const override
        {
            return EditorMode::Fill;
        }

    private:
        Application& app_;
    };

}

#endif 