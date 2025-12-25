#include "MoveCommand.h"
#include "Geometry.h"
#include <iostream>

namespace geom
{
    MoveCommand::MoveCommand(std::vector<std::shared_ptr<IGeometry>> shapes, float dx, float dy)
        : m_shapes(std::move(shapes))
        , m_dx(dx)
        , m_dy(dy)
        , m_executed(false)
    {
    }

    void MoveCommand::Execute()
    {
        // Если команда еще не была выполнена - выполняем
        if (!m_executed)
        {
            for (auto& shape : m_shapes)
            {
                shape->MoveBy(m_dx, m_dy);
            }
            m_executed = true;
        }
    }

    void MoveCommand::Undo()
    {
        // Если команда была выполнена - отменяем
        if (m_executed)
        {
            for (auto& shape : m_shapes)
            {
                shape->MoveBy(-m_dx, -m_dy);
            }
            m_executed = false;
        }
    }
}