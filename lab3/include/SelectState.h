    #ifndef GEOM_VISUALIZER_SELECT_STATE_H
#define GEOM_VISUALIZER_SELECT_STATE_H

#include "EditorState.h"

namespace geom
{

    class Application;

    class SelectState : public IEditorState
    {
    public:
        explicit SelectState(Application& app);
        void OnMousePress(const sf::Vector2f& pos) override;    
        void OnMouseMove(const sf::Vector2f& pos) override;     
        void OnMouseRelease(const sf::Vector2f& pos) override;  
        EditorMode GetMode() const override { return EditorMode::Select; }

    private:
        Application& app_;
    };

} 

#endif 