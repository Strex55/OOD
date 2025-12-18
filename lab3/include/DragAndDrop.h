#ifndef GEOM_VISUALIZER_DRAG_AND_DROP_H
#define GEOM_VISUALIZER_DRAG_AND_DROP_H

#include "Geometry.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace geom
{

    class DragDropManager
    {
    public:
        void StartDragging(const sf::Vector2f& mousePosition);
        void UpdateDragging(const sf::Vector2f& mousePosition,
            std::vector<std::shared_ptr<IGeometry>>& selected);
        void StopDragging();

        bool IsDragging() const { return isDragging_; }

    private:
        bool isDragging_ = false;
        sf::Vector2f lastMousePosition_;
    };

} 

#endif