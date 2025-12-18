#include "FillState.h"
#include "Application.h"
#include "ChangeStyleCommand.h"
#include "Geometry.h"
#include <algorithm>

namespace geom
{

    FillState::FillState(Application& app)
        : app_(app)
    {
    }

    void FillState::OnMousePress(const sf::Vector2f& pos)
    {
        auto& shapes = app_.GetShapes();

        std::shared_ptr<IGeometry> clickedShape = nullptr;
        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it)
        {
            if ((*it)->ContainsPoint(pos))
            {
                clickedShape = *it;
                break;
            }
        }

        if (clickedShape)
        {
            // НЕ выделяем фигуру в режиме Fill - убираем эту строку:
            // app_.SelectShape(clickedShape, false);

            // Вместо этого просто меняем цвет заливки без выделения
            std::vector<std::shared_ptr<IGeometry>> shapesToChange = { clickedShape };

            auto cmd = std::make_unique<ChangeStyleCommand>(
                shapesToChange,
                clickedShape->GetFillColor(),
                app_.GetFillColor(),
                clickedShape->GetOutlineColor(),
                clickedShape->GetOutlineColor(),
                clickedShape->GetOutlineThickness(),
                clickedShape->GetOutlineThickness()
            );

            app_.ExecuteCommand(std::move(cmd));

            // Очищаем выделение, если что-то было выделено ранее
            app_.ClearSelection();
        }
    }

    void FillState::OnMouseMove(const sf::Vector2f& pos)
    {
        (void)pos; // Подавление предупреждения
    }

    void FillState::OnMouseRelease(const sf::Vector2f& pos)
    {
        (void)pos; // Подавление предупреждения
    }

}