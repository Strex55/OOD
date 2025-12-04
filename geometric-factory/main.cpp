#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
// #include <SFML/Graphics.hpp>
#include "Functions.h"
#include "ShapeFactory.h"
#include "FileShapeParser.h"

class GeometryApplication {
private:
    std::vector<std::unique_ptr<IShape>> m_shapes;
    // sf::RenderWindow m_window;
    ShapeFactory m_factory;

public:
    // GeometryApplication() : m_window(sf::VideoMode(800, 600), "Geometry Factory Visualizer") {}
    GeometryApplication() {}

    bool LoadShapesFromFile(const std::string& filename) {
        // ваш существующий код без изменений
    }

    void SaveResultsToFile(const std::string& filename) {
        // ваш существующий код без изменений
    }

    void RunCalculationsOnly() {
        // ваш существующий код без изменений
    }

    void RunVisualization() {
        if (m_shapes.empty()) {
            std::cout << "No shapes to visualize" << std::endl;
            return;
        }

        std::cout << "Visualization is temporarily disabled (SFML issues)" << std::endl;
        std::cout << "Calculation results are available above" << std::endl;

        // Просто ждем нажатия Enter
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.get();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        std::cout << "Example: " << argv[0] << " input.txt output.txt" << std::endl;
        return 1;
    }

    GeometryApplication app;

    if (app.LoadShapesFromFile(argv[1])) {
        app.SaveResultsToFile(argv[2]);
        app.RunCalculationsOnly();

        std::cout << std::endl << "Press Enter to continue..." << std::endl;
        std::cin.get();
        app.RunVisualization();
    }
    else {
        std::cerr << "Failed to load shapes from " << argv[1] << std::endl;
        return 1;
    }

    return 0;
}