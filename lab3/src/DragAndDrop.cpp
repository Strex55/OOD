#include "DragAndDrop.h"

namespace geom
{
    void DragDropManager::StartDragging(const sf::Vector2f& mousePosition)
    {
        isDragging_ = true;
        lastMousePosition_ = mousePosition;
    }

    void DragDropManager::UpdateDragging(const sf::Vector2f& mousePosition,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        if (isDragging_ && !selected.empty())
        {
            const float dx = mousePosition.x - lastMousePosition_.x;
            const float dy = mousePosition.y - lastMousePosition_.y;

            // Перемещаем все выбранные фигуры визуально
            for (auto& shape : selected)
            {
                shape->MoveBy(dx, dy);
            }

            lastMousePosition_ = mousePosition;
        }
    }

    void DragDropManager::StopDragging()
    {
        isDragging_ = false;
    }
}