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
        void selectAtPosition(const sf::Vector2f& position,
            const std::vector<std::shared_ptr<IGeometry>>& shapes,
            bool addToSelection);

        void clearSelection();
        void toggleSelection(const std::shared_ptr<IGeometry>& shape);

        const std::vector<std::shared_ptr<IGeometry>>& getSelected() const { return selected_; }
        bool isEmpty() const { return selected_.empty(); }

    private:
        std::vector<std::shared_ptr<IGeometry>> selected_;
    };

} 

#endif