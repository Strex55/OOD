#include "ShapeFactory.h"
#include <algorithm>
#include <cctype>

bool ParseColor(const std::string& colorStr, uint32_t& color) {
    try {
        color = std::stoul(colorStr, nullptr, 16);
        return true;
    }
    catch (...) {
        return false;
    }
}

// TriangleCreator implementation для нового формата
std::unique_ptr<IShape> TriangleCreator::CreateShape(const std::vector<sf::Vector2f>& points, float radius) {
    if (points.size() != 3) {
        return nullptr;
    }

    // Конвертируем SFML Vector2f в наши CPoint
    CPoint p1(points[0].x, points[0].y);
    CPoint p2(points[1].x, points[1].y);
    CPoint p3(points[2].x, points[2].y);

    // Используем стандартные цвета для новой задачи
    return std::make_unique<CTriangle>(p1, p2, p3, 0xFF0000, 0x00FF00);
}

bool TriangleCreator::CanCreate(const std::string& type) const {
    std::string upperType = type;
    std::transform(upperType.begin(), upperType.end(), upperType.begin(),
        [](unsigned char c) { return std::toupper(c); });

    return upperType == "TRIANGLE";
}

// RectangleCreator implementation для нового формата
std::unique_ptr<IShape> RectangleCreator::CreateShape(const std::vector<sf::Vector2f>& points, float radius) {
    if (points.size() != 2) {
        return nullptr;
    }

    // Для прямоугольника: points[0] - левый верхний, points[1] - правый нижний
    float width = points[1].x - points[0].x;
    float height = points[1].y - points[0].y;

    if (width < 0 || height < 0) {
        return nullptr;
    }

    CPoint leftTop(points[0].x, points[0].y);

    return std::make_unique<CRectangle>(leftTop, width, height, 0x00FF00, 0x0000FF);
}

bool RectangleCreator::CanCreate(const std::string& type) const {
    std::string upperType = type;
    std::transform(upperType.begin(), upperType.end(), upperType.begin(),
        [](unsigned char c) { return std::toupper(c); });

    return upperType == "RECTANGLE";
}

// CircleCreator implementation для нового формата
std::unique_ptr<IShape> CircleCreator::CreateShape(const std::vector<sf::Vector2f>& points, float radius) {
    if (points.size() != 1 || radius <= 0) {
        return nullptr;
    }

    CPoint center(points[0].x, points[0].y);

    return std::make_unique<CCircle>(center, radius, 0x0000FF, 0xFF00FF);
}

bool CircleCreator::CanCreate(const std::string& type) const {
    std::string upperType = type;
    std::transform(upperType.begin(), upperType.end(), upperType.begin(),
        [](unsigned char c) { return std::toupper(c); });

    return upperType == "CIRCLE";
}

// ShapeFactory implementation
ShapeFactory::ShapeFactory() {
    // Регистрируем создателей для нового формата
    RegisterCreator(std::make_unique<TriangleCreator>());
    RegisterCreator(std::make_unique<RectangleCreator>());
    RegisterCreator(std::make_unique<CircleCreator>());
}

std::unique_ptr<IShape> ShapeFactory::CreateShape(const std::string& type,
    const std::vector<sf::Vector2f>& points,
    float radius) {
    for (auto& creator : m_creators) {
        if (creator->CanCreate(type)) {
            return creator->CreateShape(points, radius);
        }
    }
    return nullptr;
}

void ShapeFactory::RegisterCreator(std::unique_ptr<ShapeCreator> creator) {
    m_creators.push_back(std::move(creator));
}