#ifndef GEOM_VISUALIZER_CHANGE_STYLE_COMMAND_H
#define GEOM_VISUALIZER_CHANGE_STYLE_COMMAND_H

#include "Command.h"
#include "Geometry.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace geom
{

    class ChangeStyleCommand : public ICommand
    {
    public:
        ChangeStyleCommand(
            std::vector<std::shared_ptr<IGeometry>> shapes,
            const sf::Color& oldFillColor,
            const sf::Color& newFillColor,
            const sf::Color& oldOutlineColor,
            const sf::Color& newOutlineColor,
            float oldThickness,
            float newThickness
        );

        void Execute() override;
        void Undo() override;

    private:
        std::vector<std::shared_ptr<IGeometry>> m_shapes;

        // Старые стили (для отмены)
        sf::Color m_oldFillColor;
        sf::Color m_oldOutlineColor;
        float m_oldThickness;

        // Новые стили (для выполнения)
        sf::Color m_newFillColor;
        sf::Color m_newOutlineColor;
        float m_newThickness;

        bool m_executed = false;
    };

} 

#endif 