#ifndef GEOM_VISUALIZER_APP_H
#define GEOM_VISUALIZER_APP_H

#include "Geometry.h"
#include "Parser.h"
#include "SelectionManager.h"
#include "DragAndDrop.h"
#include "CompositeManager.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace geom
{

    class App
    {
    public:
        int run(int argc, char** argv);

    private:
        struct Config
        {
            std::string inputPath = "input.txt";
            std::string outputPath = "output.txt";
            bool noGui = false;
        };

        Config parseArguments(int argc, char** argv);
        void runVisualization();

        void processEvent(const sf::Event& event);
        void handleKeyPress(const sf::Event::KeyPressed& keyEvent);

        void drawSelectionBoxes(sf::RenderTarget& target);

        // Данные
        sf::RenderWindow window_;
        std::vector<std::shared_ptr<IGeometry>> shapes_;

        // Менеджеры
        SelectionManager selectionManager_;
        DragDropManager dragDropManager_;
        CompositeManager compositeManager_;

        Config config_;
        Parser parser_;
    };

} 

#endif