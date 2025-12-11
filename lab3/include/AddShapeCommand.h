#ifndef GEOM_VISUALIZER_ADD_SHAPE_COMMAND_H
#define GEOM_VISUALIZER_ADD_SHAPE_COMMAND_H

#include "Command.h"
#include <memory>

namespace geom {
    class Application;
    class IGeometry;

    class AddShapeCommand : public ICommand {
    public:
        AddShapeCommand(Application& app, std::shared_ptr<IGeometry> shape);
        void Execute() override;
        void Undo() override;

    private:
        Application& app_;
        std::shared_ptr<IGeometry> shape_;
    };
}
#endif