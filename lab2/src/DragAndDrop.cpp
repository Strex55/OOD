#include "DragAndDrop.h"

namespace geom
{

    void DragAndDrop::startDragging(const sf::Vector2f& mousePosition)
    {
        isDragging_ = true;
        lastMousePosition_ = mousePosition;
    }

    void DragAndDrop::updateDragging(const sf::Vector2f& mousePosition,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        if (isDragging_ && !selected.empty())
        {
            const float dx = mousePosition.x - lastMousePosition_.x;
            const float dy = mousePosition.y - lastMousePosition_.y;

            if (dx != 0.0f || dy != 0.0f)
            {
                for (auto& shape : selected)
                {
                    shape->moveBy(dx, dy);
                }

                lastMousePosition_ = mousePosition;
            }
        }
    }

    void DragAndDrop::stopDragging()
    {
        isDragging_ = false;
    }

} 