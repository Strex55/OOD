#pragma once
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "IShape.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

// Базовый класс создателя для нового формата данных
class ShapeCreator {
public:
    virtual ~ShapeCreator() = default;
    virtual std::unique_ptr<IShape> CreateShape(const std::vector<sf::Vector2f>& points, float radius = 0) = 0;
    virtual std::string GetSupportedType() const = 0;
    virtual bool CanCreate(const std::string& type) const = 0;
};

// Конкретные создатели для нового формата
class TriangleCreator : public ShapeCreator {
public:
    std::unique_ptr<IShape> CreateShape(const std::vector<sf::Vector2f>& points, float radius = 0) override;
    std::string GetSupportedType() const override { return "TRIANGLE"; }
    bool CanCreate(const std::string& type) const override;
};

class RectangleCreator : public ShapeCreator {
public:
    std::unique_ptr<IShape> CreateShape(const std::vector<sf::Vector2f>& points, float radius = 0) override;
    std::string GetSupportedType() const override { return "RECTANGLE"; }
    bool CanCreate(const std::string& type) const override;
};

class CircleCreator : public ShapeCreator {
public:
    std::unique_ptr<IShape> CreateShape(const std::vector<sf::Vector2f>& points, float radius = 0) override;
    std::string GetSupportedType() const override { return "CIRCLE"; }
    bool CanCreate(const std::string& type) const override;
};

// Фабрика для нового формата
class ShapeFactory {
private:
    std::vector<std::unique_ptr<ShapeCreator>> m_creators;

public:
    ShapeFactory();
    std::unique_ptr<IShape> CreateShape(const std::string& type, const std::vector<sf::Vector2f>& points, float radius = 0);
    void RegisterCreator(std::unique_ptr<ShapeCreator> creator);
};

// Вспомогательная функция остается
bool ParseColor(const std::string& colorStr, uint32_t& color);