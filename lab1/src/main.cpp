//"D:\Nikita\3_COURSE\OOD\lab1\build\Release\geom_app.exe" --input "D:\Nikita\3_COURSE\OOD\lab1\input.txt" --output "D:\Nikita\3_COURSE\OOD\lab1\output.txt"

#include "Parser.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace geom;

int main(int argc, char** argv) {
  std::string inputPath = "input.txt";
  std::string outputPath = "output.txt";
  bool noGui = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--input" && i + 1 < argc) inputPath = argv[++i];
    else if (arg == "--output" && i + 1 < argc) outputPath = argv[++i];
    else if (arg == "--no-gui") noGui = true;
  }

  Parser parser;
  auto shapes = parser.parseFile(inputPath);
  if (shapes.empty()) {
    std::cerr << "No shapes parsed from " << inputPath << "\n";
  }
  Parser::writeResults(outputPath, shapes);

  if (!noGui) {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800u, 600u)), "Geometry Visualization");

    while (window.isOpen()) {
      while (auto ev = window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) window.close();
      }
      window.clear(sf::Color::White);
      for (const auto& s : shapes) {
        s->draw(window);
      }
      window.display();
    }
  }

  return 0;
}