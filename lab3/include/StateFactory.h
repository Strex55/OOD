#ifndef GEOM_VISUALIZER_STATE_FACTORY_H
#define GEOM_VISUALIZER_STATE_FACTORY_H

#include "EditorState.h"
#include <memory>

namespace geom
{

    class Application;

    class StateFactory
    {
    public:
        static std::unique_ptr<IEditorState> CreateState(
            EditorMode mode,
            Application& app
        );
    };

} 

#endif 