#pragma once
#include "IShape.h"
#include <SFML/Graphics.hpp>
#include <memory>

class IVisualShape : public IShape {
public:
    virtual ~IVisualShape() = default;
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void SetPosition(float x, float y) = 0;
    virtual sf::FloatRect GetBounds() const = 0;
    virtual std::string GetType() const = 0;
};