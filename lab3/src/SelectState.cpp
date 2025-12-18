#include "SelectState.h"
#include "Application.h"
#include "Geometry.h"
#include <algorithm>

namespace geom
{

    SelectState::SelectState(Application& app) : app_(app)
    {
    }

    void SelectState::OnMousePress(const sf::Vector2f& pos)
    {
        std::shared_ptr<IGeometry> hit = nullptr;
        auto& shapes = app_.GetShapes();

        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it)
        {
            if ((*it)->ContainsPoint(pos))
            {
                hit = *it;
                break;
            }
        }

        const bool addToSelection = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift);

        if (!addToSelection)
        {
            app_.ClearSelection();
        }

        if (hit)
        {
            auto& selected = app_.GetSelected();
            auto found = std::find(selected.begin(), selected.end(), hit);

            if (addToSelection && found != selected.end())
            {
                selected.erase(found);
            }
            else
            {
                app_.SelectShape(hit, addToSelection);
            }
        }
    }

    void SelectState::OnMouseMove(const sf::Vector2f& pos)
    {
        auto& selected = app_.GetSelected();
        if (!selected.empty())
        {
        }
    }

    void SelectState::OnMouseRelease(const sf::Vector2f& pos)
    {
    }

}