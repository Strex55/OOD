#include "CompositeManager.h"
#include <algorithm>

namespace geom 
{

    void CompositeManager::PerformOperation(Operation op,
        std::vector<std::shared_ptr<IGeometry>>& shapes,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        switch (op) 
        {
        case Operation::Group:
            if (CanGroup(selected)) 
            {
                GroupSelected(shapes, selected);
            }
            break;

        case Operation::Ungroup:
            if (selected.size() == 1 && CanUngroup(selected.front())) 
            {
                UngroupSelected(shapes, selected);
            }
            break;

        default:
            // Неподдерживаемая операция
            break;
        }
    }

    void CompositeManager::GroupSelected(std::vector<std::shared_ptr<IGeometry>>& shapes,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        auto group = std::make_shared<CompositeShape>();

        for (const auto& shape : selected) 
        {
            group->Add(shape);
        }

        // Удаляем выделенные фигуры из основного списка
        shapes.erase(
            std::remove_if(shapes.begin(), shapes.end(),
                [&](const std::shared_ptr<IGeometry>& shape)
                {
                    return std::find(selected.begin(), selected.end(), shape) != selected.end();
                }),
            shapes.end()
        );

        // Добавляем группу в основной список
        shapes.push_back(group);

        // Обновляем выделение (теперь выделена только группа)
        selected.clear();
        selected.push_back(group);
    }

    void CompositeManager::UngroupSelected(std::vector<std::shared_ptr<IGeometry>>& shapes,
        std::vector<std::shared_ptr<IGeometry>>& selected)
    {
        auto group = std::dynamic_pointer_cast<CompositeShape>(selected.front());

        if (group) 
        {
            // Удаляем группу из основного списка
            shapes.erase(
                std::remove(shapes.begin(), shapes.end(), group),
                shapes.end()
            );

            // Добавляем дочерние фигуры обратно в основной список
            for (const auto& child : group->GetChildren()) 
            {
                shapes.push_back(child);
            }

            selected.clear();
        }
    }

    bool CompositeManager::CanGroup(const std::vector<std::shared_ptr<IGeometry>>& selected) const
    {
        return selected.size() >= 2;
    }

    bool CompositeManager::CanUngroup(const std::shared_ptr<IGeometry>& shape) const
    {
        return std::dynamic_pointer_cast<CompositeShape>(shape) != nullptr;
    }

} 