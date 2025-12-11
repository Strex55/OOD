#include "CompositeManager.h"
#include <algorithm>

namespace geom
{

    void CompositeManager::performOperation(Operation op,
        std::vector<std::shared_ptr<IGeometry>>& shapes,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        switch (op)
        {
        case Operation::Group:
            if (canGroup(selected))
            {
                groupSelected(shapes, selected);
            }
            break;

        case Operation::Ungroup:
            if (selected.size() == 1 && canUngroup(selected.front()))
            {
                ungroupSelected(shapes, selected);
            }
            break;

        default:
            // ����������� ��������
            break;
        }
    }

    void CompositeManager::groupSelected(std::vector<std::shared_ptr<IGeometry>>& shapes,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        auto group = std::make_shared<CompositeShape>();

        for (const auto& shape : selected)
        {
            group->add(shape);
        }

        // ������� ��������� ������ �� ��������� ������
        shapes.erase(
            std::remove_if(shapes.begin(), shapes.end(),
                [&](const std::shared_ptr<IGeometry>& shape)
                {
                    return std::find(selected.begin(), selected.end(), shape) != selected.end();
                }),
            shapes.end()
        );

        // ��������� ������ � �������� ������
        shapes.push_back(group);

        // ��������� ��������� (������ �������� ������ ������)
        selected.clear();
        selected.push_back(group);
    }

    void CompositeManager::ungroupSelected(std::vector<std::shared_ptr<IGeometry>>& shapes,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        auto group = std::dynamic_pointer_cast<CompositeShape>(selected.front());

        if (group)
        {
            // ������� ������ �� ��������� ������
            shapes.erase(
                std::remove(shapes.begin(), shapes.end(), group),
                shapes.end()
            );

            // ��������� �������� ������ ������� � �������� ������
            for (const auto& child : group->children())
            {
                shapes.push_back(child);
            }

            selected.clear();
        }
    }

    bool CompositeManager::canGroup(const std::vector<std::shared_ptr<IGeometry>>& selected) const
    {
        return selected.size() >= 2;
    }

    bool CompositeManager::canUngroup(const std::shared_ptr<IGeometry>& shape) const
    {
        return std::dynamic_pointer_cast<CompositeShape>(shape) != nullptr;
    }

} 