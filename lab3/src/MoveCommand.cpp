#include "MoveCommand.h"
#include "Geometry.h"

namespace geom 
{

    MoveCommand::MoveCommand(std::vector<std::shared_ptr<IGeometry>> shapes, float dx, float dy)
        : m_shapes(std::move(shapes)), m_dx(dx), m_dy(dy)
    {
    }

    void MoveCommand::Execute()
    {
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
        if (m_executed) 
        {
            // ѕровер€ем, что фигуры все еще существуют
            std::vector<std::shared_ptr<IGeometry>> validShapes;
            for (auto& shape : m_shapes) 
            {
                if (shape) 
                {
                    validShapes.push_back(shape);
                }
            }

            // ѕеремещаем обратно только валидные фигуры
            for (auto& shape : validShapes) 
            {
                shape->MoveBy(-m_dx, -m_dy);
            }
            m_executed = false;
        }
    }

} 