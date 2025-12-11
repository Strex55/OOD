#ifndef GEOM_VISUALIZER_MOVE_COMMAND_H
#define GEOM_VISUALIZER_MOVE_COMMAND_H

#include "Command.h"
#include <memory>
#include <vector>

namespace geom
{
    class IGeometry;

    class MoveCommand : public ICommand
    {
    public:
        MoveCommand(std::vector<std::shared_ptr<IGeometry>> shapes, float dx, float dy);

        void Execute() override;
        void Undo() override;

    private:
        std::vector<std::shared_ptr<IGeometry>> m_shapes;
        float m_dx, m_dy;
        bool m_executed = false;
    };
}

#endif 