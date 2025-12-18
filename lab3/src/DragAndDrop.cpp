#include "DragAndDrop.h"
#include "Application.h"
#include "MoveCommand.h"
#include <iostream>

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

            static float accumDx = 0, accumDy = 0;
            accumDx += dx;
            accumDy += dy;

            const float moveThreshold = 1.0f; // Минимальное перемещение для создания команды

            if (std::abs(accumDx) > moveThreshold || std::abs(accumDy) > moveThreshold) 
            {
                std::cout << "DragDrop: moving by (" << accumDx << ", " << accumDy << ")\n";

                auto& app = Application::GetInstance();

                std::vector<std::shared_ptr<IGeometry>> shapesToMove;
                shapesToMove.reserve(selected.size());
                for (const auto& shape : selected) 
                {
                    shapesToMove.push_back(shape);
                }

                auto cmd = std::make_unique<MoveCommand>(std::move(shapesToMove), accumDx, accumDy);
                app.ExecuteCommand(std::move(cmd));

                // Сбрасываем накопленное перемещение
                accumDx = 0;
                accumDy = 0;
            }

            lastMousePosition_ = mousePosition;
        }
    }

    void DragDropManager::StopDragging()
    {
        isDragging_ = false;
    }

} 