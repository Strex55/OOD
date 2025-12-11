#include "FillState.h"
#include "Application.h"
#include "ChangeStyleCommand.h"
#include "Geometry.h"
#include <algorithm>

namespace geom
{

    FillState::FillState(Application& app)
        : m_app(app)
    {
    }

    void FillState::OnMousePress(const sf::Vector2f& pos)
    {
        auto& shapes = m_app.GetShapes();

        // Find clicked shape (from top to bottom)
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
            std::vector<std::shared_ptr<IGeometry>> shapesToChange = { clickedShape };

            auto cmd = std::make_unique<ChangeStyleCommand>(
                shapesToChange,
                clickedShape->GetFillColor(),      
                m_app.GetFillColor(),              
                clickedShape->GetOutlineColor(),   
                clickedShape->GetOutlineColor(),   
                clickedShape->GetOutlineThickness(), 
                clickedShape->GetOutlineThickness()  
            );

            m_app.ExecuteCommand(std::move(cmd));
            m_app.SelectShape(clickedShape, false);
        }
    }

    void FillState::OnMouseMove(const sf::Vector2f& pos)
    {
    }

    void FillState::OnMouseRelease(const sf::Vector2f& pos)
    {
    }

} 