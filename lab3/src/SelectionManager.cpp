#include "SelectionManager.h"
#include <algorithm>

namespace geom
{

    void SelectionManager::selectAtPosition(const sf::Vector2f& position,
        const std::vector<std::shared_ptr<IGeometry>>& shapes,
        bool addToSelection)
    {
        if (!addToSelection)
        {
            selected_.clear();
        }

        // ���� ������ ������ ���� (�������� ������� ��� hit-test)
        std::shared_ptr<IGeometry> hitShape = nullptr;

        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it)
        {
            if ((*it)->containsPoint(position))
            {
                hitShape = *it;
                break;
            }
        }

        if (hitShape)
        {
            // ���� Shift ����� - ����������� ���������
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

    void SelectionManager::clearSelection()
    {
        selected_.clear();
    }

    void SelectionManager::toggleSelection(const std::shared_ptr<IGeometry>& shape)
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