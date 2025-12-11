#include "StateFactory.h"
#include "SelectState.h"
#include "FillState.h"
#include "AddShapeState.h"

namespace geom {

    std::unique_ptr<IEditorState> StateFactory::CreateState(EditorMode mode, Application& app) {
    switch (mode) {
        case EditorMode::Select:
        return std::make_unique<SelectState>(app);
     case EditorMode::Fill:
          return std::make_unique<FillState>(app);
     case EditorMode::AddTriangle:
       return std::make_unique<AddShapeState>(app, EditorMode::AddTriangle);
     case EditorMode::AddRectangle:
       return std::make_unique<AddShapeState>(app, EditorMode::AddRectangle);
     case EditorMode::AddCircle:
       return std::make_unique<AddShapeState>(app, EditorMode::AddCircle);
     default:
       return std::make_unique<SelectState>(app);
        }
    }

}