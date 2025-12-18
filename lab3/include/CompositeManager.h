#ifndef GEOM_VISUALIZER_COMPOSITE_MANAGER_H
#define GEOM_VISUALIZER_COMPOSITE_MANAGER_H

#include "CompositeShape.h"
#include <memory>
#include <vector>

namespace geom
{

    class CompositeManager
    {
    public:
        enum class Operation
        {
            Group,
            Ungroup
        };

        void PerformOperation(Operation op,
            std::vector<std::shared_ptr<IGeometry>>& shapes,
            std::vector<std::shared_ptr<IGeometry>>& selected);

    private:
        void GroupSelected(std::vector<std::shared_ptr<IGeometry>>& shapes,
            std::vector<std::shared_ptr<IGeometry>>& selected);

        void UngroupSelected(std::vector<std::shared_ptr<IGeometry>>& shapes,
            std::vector<std::shared_ptr<IGeometry>>& selected);

        bool CanGroup(const std::vector<std::shared_ptr<IGeometry>>& selected) const;
        bool CanUngroup(const std::shared_ptr<IGeometry>& shape) const;
    };

}

#endif 