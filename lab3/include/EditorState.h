#ifndef GEOM_VISUALIZER_EDITOR_STATE_H
#define GEOM_VISUALIZER_EDITOR_STATE_H

#include <SFML/Graphics.hpp>

namespace geom
{

    enum class EditorMode
    {
        Select,
        Fill,
        AddTriangle,
        AddRectangle,
        AddCircle
    };

    class IEditorState
    {
    public:
        virtual ~IEditorState() = default;
        virtual void OnMousePress(const sf::Vector2f& pos) = 0;     
        virtual void OnMouseMove(const sf::Vector2f& pos) = 0;      
        virtual void OnMouseRelease(const sf::Vector2f& pos) = 0;   
        virtual EditorMode GetMode() const = 0;
    };

} 

#endif 