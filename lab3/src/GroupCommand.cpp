#include "GroupCommand.h"
#include "CompositeShape.h"
#include "Application.h"
#include <algorithm>
#include <iostream>

namespace geom 
{

    GroupCommand::GroupCommand(Operation op,
        std::vector<std::shared_ptr<IGeometry>>& allShapes,
        std::vector<std::shared_ptr<IGeometry>>& selectedShapes)
        : operation_(op)
        , allShapes_(allShapes)
        , selectedShapes_(selectedShapes) 
    {
    }

    void GroupCommand::Execute()
    {
        // Отладочный вывод
        std::cout << "GroupCommand::Execute - Operation: "
            << (operation_ == Operation::Group ? "Group" : "Ungroup")
            << ", Selected shapes: " << selectedShapes_.size()
            << ", All shapes: " << allShapes_.size() << std::endl;

        if (operation_ == Operation::Group) 
        {
            // Проверяем, можно ли группировать
            if (selectedShapes_.size() < 2) return;

            // Создаем новую группу
            createdGroup_ = std::make_shared<CompositeShape>();
            originalChildren_ = selectedShapes_;

            // Добавляем все выбранные фигуры в группу
            for (const auto& shape : originalChildren_) 
            {
                createdGroup_->Add(shape);
            }

            // Удаляем исходные фигуры из основного списка
            for (const auto& shape : originalChildren_) 
            {
                allShapes_.erase(
                    std::remove(allShapes_.begin(), allShapes_.end(), shape),
                    allShapes_.end()
                );
            }

            // Добавляем группу в основной список
            allShapes_.push_back(createdGroup_);

            // Обновляем выделение (теперь выделена только группа)
            selectedShapes_.clear();
            selectedShapes_.push_back(createdGroup_);

        }
        else if (operation_ == Operation::Ungroup) 
        {
            // Проверяем, можно ли разгруппировать
            if (selectedShapes_.size() != 1) return;

            auto group = std::dynamic_pointer_cast<CompositeShape>(selectedShapes_[0]);
            if (!group) return;

            // Сохраняем группу для отмены
            createdGroup_ = group;
            originalChildren_ = group->GetChildren();

            // Удаляем группу из основного списка
            allShapes_.erase(
                std::remove(allShapes_.begin(), allShapes_.end(), createdGroup_),
                allShapes_.end()
            );

            // Добавляем дочерние фигуры обратно в основной список
            for (const auto& child : originalChildren_) 
            {
                allShapes_.push_back(child);
            }

            // Обновляем выделение (выделяем все дочерние фигуры)
            selectedShapes_.clear();
            selectedShapes_ = originalChildren_;
        }
    }

    void GroupCommand::Undo()
    {
        if (operation_ == Operation::Group) {
            // Отмена группировки = разгруппировка
            if (!createdGroup_) return;

            // Удаляем группу из основного списка
            allShapes_.erase(
                std::remove(allShapes_.begin(), allShapes_.end(), createdGroup_),
                allShapes_.end()
            );

            // Добавляем исходные фигуры обратно
            for (const auto& child : originalChildren_) 
            {
                allShapes_.push_back(child);
            }

            // Восстанавливаем выделение
            selectedShapes_.clear();
            selectedShapes_ = originalChildren_;

        }
        else if (operation_ == Operation::Ungroup) 
        {
            // Отмена разгруппировки = группировка
            if (!createdGroup_) return;

            // Удаляем дочерние фигуры из основного списка
            for (const auto& child : originalChildren_) 
            {
                allShapes_.erase(
                    std::remove(allShapes_.begin(), allShapes_.end(), child),
                    allShapes_.end()
                );
            }

            // Добавляем группу обратно
            allShapes_.push_back(createdGroup_);

            // Восстанавливаем выделение (только группа)
            selectedShapes_.clear();
            selectedShapes_.push_back(createdGroup_);
        }
    }

} 