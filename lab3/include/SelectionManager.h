#ifndef GEOM_VISUALIZER_SELECTION_MANAGER_H
#define GEOM_VISUALIZER_SELECTION_MANAGER_H

#include "Geometry.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

namespace geom
{

    class SelectionManager
    {
    public:
        void SelectAtPosition(const sf::Vector2f& position,
            const std::vector<std::shared_ptr<IGeometry>>& shapes,
            bool AddToSelection);

        void ClearSelection();
        void ToggleSelection(const std::shared_ptr<IGeometry>& shape);

        const std::vector<std::shared_ptr<IGeometry>>& GetSelected() const { return selected_; }
        bool IsEmpty() const { return selected_.empty(); }
        int GetSelectionCount() const { return static_cast<int>(selected_.size()); }

    private:
        std::vector<std::shared_ptr<IGeometry>> selected_;
    };

} 

#endif 