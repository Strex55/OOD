#include "Parser.h"
#include "CompositeShape.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <algorithm>

using namespace geom;

static void drawSelectionBox(sf::RenderTarget& target, const sf::FloatRect& r) {
  sf::RectangleShape box(sf::Vector2f(r.size.x, r.size.y));
  box.setPosition(sf::Vector2f(r.position.x, r.position.y));
  box.setFillColor(sf::Color(0, 0, 0, 0));
  box.setOutlineColor(sf::Color(0, 120, 255));
  box.setOutlineThickness(1.5f);
  target.draw(box);
  const float s = 6.f;
  sf::RectangleShape handle(sf::Vector2f(s, s));
  handle.setFillColor(sf::Color(0, 120, 255));
  const sf::Vector2f corners[4] = {
    {r.position.x - s/2.f, r.position.y - s/2.f},
    {r.position.x + r.size.x - s/2.f, r.position.y - s/2.f},
    {r.position.x - s/2.f, r.position.y + r.size.y - s/2.f},
    {r.position.x + r.size.x - s/2.f, r.position.y + r.size.y - s/2.f}
  };
  for (auto c : corners) {
    handle.setPosition(c);
    target.draw(handle);
  }
}

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
    window.setFramerateLimit(60);

    std::vector<std::shared_ptr<IGeometry>> selected;
    bool dragging = false;
    sf::Vector2f lastMouse{};

    while (window.isOpen()) {
      while (auto ev = window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) {
          window.close();
        } else if (ev->is<sf::Event::MouseButtonPressed>()) {
          if (auto mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
          if (mb->button == sf::Mouse::Button::Left) {
            const sf::Vector2f pos = sf::Vector2f(static_cast<float>(mb->position.x), static_cast<float>(mb->position.y));
            // hit test from top to bottom
            std::shared_ptr<IGeometry> hit = nullptr;
            for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
              if ((*it)->containsPoint(pos)) { hit = *it; break; }
            }
            const bool addToSelection = sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift)
                                     || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift);
            if (!addToSelection) selected.clear();
            if (hit) {
              // toggle if Shift
              auto found = std::find(selected.begin(), selected.end(), hit);
              if (addToSelection && found != selected.end()) {
                selected.erase(found);
              } else {
                selected.push_back(hit);
              }
              dragging = true;
              lastMouse = pos;
            } else {
              dragging = false;
            }
          }
          }
        } else if (ev->is<sf::Event::MouseButtonReleased>()) {
          dragging = false;
        } else if (ev->is<sf::Event::MouseMoved>()) {
          if (auto mm = ev->getIf<sf::Event::MouseMoved>()) {
          const sf::Vector2f pos = sf::Vector2f(static_cast<float>(mm->position.x), static_cast<float>(mm->position.y));
          if (dragging && !selected.empty()) {
            const float dx = pos.x - lastMouse.x;
            const float dy = pos.y - lastMouse.y;
            if (dx != 0.f || dy != 0.f) {
              for (auto& s : selected) s->moveBy(dx, dy);
              lastMouse = pos;
            }
          }}
        } else if (ev->is<sf::Event::KeyPressed>()) {
          if (auto kp = ev->getIf<sf::Event::KeyPressed>()) {
          // Treat Control; combine event flags and live state
          const bool ctrl = kp->control || kp->system
                         || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl)
                         || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl);
          const bool keyG = (kp->scancode == sf::Keyboard::Scancode::G)
                         || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::G);
          const bool keyU = (kp->scancode == sf::Keyboard::Scancode::U)
                         || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::U);
          if (ctrl && keyG) {
            if (selected.size() >= 2) {
              auto group = std::make_shared<CompositeShape>();
              for (const auto& s : selected) {
                group->add(s);
              }
              // remove selected from root list
              shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [&](const std::shared_ptr<IGeometry>& s){
                return std::find(selected.begin(), selected.end(), s) != selected.end();
              }), shapes.end());
              shapes.push_back(group);
              selected.clear();
              selected.push_back(group);
            }
          } else if (ctrl && keyU) {
            if (selected.size() == 1) {
              auto group = std::dynamic_pointer_cast<CompositeShape>(selected.front());
              if (group) {
                // remove group from roots
                shapes.erase(std::remove(shapes.begin(), shapes.end(), group), shapes.end());
                // add back children
                for (const auto& child : group->children()) shapes.push_back(child);
                selected.clear();
              }
            }
          }}
        }
      }
      window.clear(sf::Color::White);
      for (const auto& s : shapes) {
        s->draw(window);
      }
      for (const auto& s : selected) {
        drawSelectionBox(window, s->getBounds());
      }
      window.display();
    }
  }

  return 0;
}