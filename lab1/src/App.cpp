#include "App.h"
#include "Parser.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace geom
{

    int App::run(int argc, char** argv)
    {
        Config config = parseArguments(argc, argv);
        runVisualization(config.inputPath, config.outputPath, config.noGui);
        return 0;
    }

    App::Config App::parseArguments(int argc, char** argv)
    {
        Config config;
        config.inputPath = "input.txt";
        config.outputPath = "output.txt";

        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];

            if (arg == "--input" && i + 1 < argc)
            {
                config.inputPath = argv[++i];
            }
            else if (arg == "--output" && i + 1 < argc)
            {
                config.outputPath = argv[++i];
            }
            else if (arg == "--no-gui")
            {
                config.noGui = true;
            }
        }

        return config;
    }

    void App::runVisualization(const std::string& inputPath, const std::string& outputPath, bool noGui)
    {
        Parser parser;
        auto shapes = parser.parseFile(inputPath);

        if (shapes.empty())
        {
            std::cerr << "No shapes parsed from " << inputPath << "\n";
            return;
        }

        Parser::writeResults(outputPath, shapes);

        if (noGui)
        {
            return;
        }

        // SFML 3.0 API - используем sf::Vector2u для размеров окна
        sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800u, 600u)), "Geometry Visualization");

        while (window.isOpen())
        {
            // SFML 3.0 API - pollEvent возвращает optional
            while (auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            window.clear(sf::Color::White);

            for (const auto& shape : shapes)
            {
                shape->draw(window);
            }

            window.display();
        }
    }

} 