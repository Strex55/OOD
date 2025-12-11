#include "ChangeStyleCommand.h"
#include <iostream>

namespace geom
{
    ChangeStyleCommand::ChangeStyleCommand(
        std::vector<std::shared_ptr<IGeometry>> shapes,
        const sf::Color& oldFillColor,
        const sf::Color& newFillColor,
        const sf::Color& oldOutlineColor,
        const sf::Color& newOutlineColor,
        float oldThickness,
        float newThickness
    )
        : m_shapes(std::move(shapes))
        , m_oldFillColor(oldFillColor)
        , m_newFillColor(newFillColor)
        , m_oldOutlineColor(oldOutlineColor)
        , m_newOutlineColor(newOutlineColor)
        , m_oldThickness(oldThickness)
        , m_newThickness(newThickness)
    {
    }

    void ChangeStyleCommand::Execute()
    {
        if (!m_executed)
        {
            for (auto& shape : m_shapes)
            {
                shape->SetFillColor(m_newFillColor);
                shape->SetOutlineColor(m_newOutlineColor);
                shape->SetOutlineThickness(m_newThickness);
            }
            m_executed = true;
        }
    }

    void ChangeStyleCommand::Undo()
    {
        if (m_executed)
        {
            for (auto& shape : m_shapes)
            {
                shape->SetFillColor(m_oldFillColor);
                shape->SetOutlineColor(m_oldOutlineColor);
                shape->SetOutlineThickness(m_oldThickness);
            }
            m_executed = false;
        }
    }

} 