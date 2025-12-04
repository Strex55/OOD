#include "App.h"
#include <iostream>

namespace geom
{

    int App::run(int argc, char** argv)
    {
        config_ = parseArguments(argc, argv);

        shapes_ = parser_.parseFile(config_.inputPath);
        if (shapes_.empty())
        {
            std::cerr << "No shapes parsed from " << config_.inputPath << "\n";
            return 1;
        }

        parser_.writeResults(config_.outputPath, shapes_);

        if (!config_.noGui)
        {
            runVisualization();
        }

        return 0;
    }

    App::Config App::parseArguments(int argc, char** argv)
    {
        Config config;

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

    void App::runVisualization()
    {
        window_.create(sf::VideoMode(sf::Vector2u(800u, 600u)), "Geometry Visualization");
        window_.setFramerateLimit(60);

        while (window_.isOpen())
        {
            // Обработка событий с помощью switch
            while (auto event = window_.pollEvent())
            {
                processEvent(*event);
            }

            window_.clear(sf::Color::White);

            for (const auto& shape : shapes_)
            {
                shape->draw(window_);
            }

            drawSelectionBoxes(window_);

            window_.display();
        }
    }

    void App::processEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                const sf::Vector2f position(
                    static_cast<float>(event.mouseButton.position.x),
                    static_cast<float>(event.mouseButton.position.y)
                );

                const bool addToSelection =
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift);

                selectionManager_.selectAtPosition(position, shapes_, addToSelection);

                if (!selectionManager_.isEmpty())
                {
                    dragDropManager_.startDragging(position);
                }
            }
            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                dragDropManager_.stopDragging();
            }
            break;

        case sf::Event::MouseMoved:
        {
            const sf::Vector2f position(
                static_cast<float>(event.mouseMove.position.x),
                static_cast<float>(event.mouseMove.position.y)
            );

            auto& selected = const_cast<std::vector<std::shared_ptr<IGeometry>>&>(
                selectionManager_.getSelected()
                );

            dragDropManager_.updateDragging(position, selected);
            break;
        }

        case sf::Event::KeyPressed:
            handleKeyPress(event.key);
            break;

        default:
            // Игнорируем другие события
            break;
        }
    }

    void App::handleKeyPress(const sf::Event::KeyPressed& keyEvent)
    {
        const bool ctrlPressed =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl);

        if (!ctrlPressed) return;

        CompositeManager::Operation operation;
        bool hasOperation = false;

        switch (keyEvent.scancode)
        {
        case sf::Keyboard::Scancode::G:
            operation = CompositeManager::Operation::Group;
            hasOperation = true;
            break;

        case sf::Keyboard::Scancode::U:
            operation = CompositeManager::Operation::Ungroup;
            hasOperation = true;
            break;

        default:
            // Другие клавиши не обрабатываем
            break;
        }

        if (hasOperation)
        {
            auto& selected = const_cast<std::vector<std::shared_ptr<IGeometry>>&>(
                selectionManager_.getSelected()
                );

            compositeManager_.performOperation(operation, shapes_, selected);
        }
    }

    void App::drawSelectionBoxes(sf::RenderTarget& target)
    {
        const auto& selected = selectionManager_.getSelected();

        for (const auto& shape : selected)
        {
            const auto bounds = shape->getBounds();

            sf::RectangleShape box(sf::Vector2f(bounds.size.x, bounds.size.y));
            box.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
            box.setFillColor(sf::Color::Transparent);
            box.setOutlineColor(sf::Color(0, 120, 255));
            box.setOutlineThickness(1.5f);
            target.draw(box);

            // Маркеры по углам
            const float markerSize = 6.0f;
            sf::RectangleShape marker(sf::Vector2f(markerSize, markerSize));
            marker.setFillColor(sf::Color(0, 120, 255));

            const sf::Vector2f corners[4] = {
                {bounds.position.x - markerSize / 2.0f, bounds.position.y - markerSize / 2.0f},
                {bounds.position.x + bounds.size.x - markerSize / 2.0f, bounds.position.y - markerSize / 2.0f},
                {bounds.position.x - markerSize / 2.0f, bounds.position.y + bounds.size.y - markerSize / 2.0f},
                {bounds.position.x + bounds.size.x - markerSize / 2.0f, bounds.position.y + bounds.size.y - markerSize / 2.0f}
            };

            for (const auto& corner : corners)
            {
                marker.setPosition(corner);
                target.draw(marker);
            }
        }
    }

} 