#ifndef GEOM_VISUALIZER_GROUP_COMMAND_H
#define GEOM_VISUALIZER_GROUP_COMMAND_H

#include "Command.h"
#include <memory>
#include <vector>

namespace geom
{

    class IGeometry;
    class CompositeShape;

    class GroupCommand : public ICommand
    {
    public:
        enum class Operation { Group, Ungroup };

        GroupCommand(Operation op,
            std::vector<std::shared_ptr<IGeometry>>& allShapes,
            std::vector<std::shared_ptr<IGeometry>>& selectedShapes);

        void Execute() override;
        void Undo() override;

    private:
        Operation operation_;
        std::vector<std::shared_ptr<IGeometry>>& allShapes_;
        std::vector<std::shared_ptr<IGeometry>>& selectedShapes_;
        std::shared_ptr<CompositeShape> createdGroup_;
        std::vector<std::shared_ptr<IGeometry>> originalChildren_;
    };

} 

#endif 