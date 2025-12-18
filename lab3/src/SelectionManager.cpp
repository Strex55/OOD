#include "SelectionManager.h"
#include <algorithm>

namespace geom 
{

    void SelectionManager::SelectAtPosition(const sf::Vector2f& position,
        const std::vector<std::shared_ptr<IGeometry>>& shapes,
        bool addToSelection)
    {
        if (!addToSelection) 
        {
            selected_.clear();
        }

        // Ищем верхнюю фигуру в точке клика
        std::shared_ptr<IGeometry> hitShape = nullptr;

        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
            if ((*it)->ContainsPoint(position)) 
            {
                hitShape = *it;
                break;
            }
        }

        if (hitShape) 
        {
            // Если Shift нажат - переключаем выделение
            auto found = std::find(selected_.begin(), selected_.end(), hitShape);

            if (addToSelection && found != selected_.end()) 
            {
                selected_.erase(found);
            }
            else 
            {
                selected_.push_back(hitShape);
            }
        }
    }

    void SelectionManager::ClearSelection()
    {
        selected_.clear();
    }

    void SelectionManager::ToggleSelection(const std::shared_ptr<IGeometry>& shape)
    {
        auto it = std::find(selected_.begin(), selected_.end(), shape);

        if (it != selected_.end()) 
        {
            selected_.erase(it);
        }
        else 
        {
            selected_.push_back(shape);
        }
    }

} 