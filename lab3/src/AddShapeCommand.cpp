#include "AddShapeCommand.h"
#include "Application.h"
#include "Geometry.h"

namespace geom
{

    AddShapeCommand::AddShapeCommand(Application& app, std::shared_ptr<IGeometry> shape)
        : app_(app)
        , shape_(std::move(shape))
    {
    }

    void AddShapeCommand::Execute()
    {
        if (shape_)
        {
            app_.AddShape(shape_);
        }
    }

    void AddShapeCommand::Undo()
    {
        if (shape_)
        {
            app_.RemoveShape(shape_);
        }
    }

}