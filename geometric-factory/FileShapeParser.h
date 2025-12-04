#pragma once
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

struct ShapeData {
    std::string type;
    std::vector<sf::Vector2f> points;
    float radius = 0;
};

class FileShapeParser {
public:
    static std::vector<ShapeData> ParseFile(const std::string& filename);
    static ShapeData ParseLine(const std::string& line);

private:
    static sf::Vector2f ParsePoint(const std::string& pointStr);
    static float ParseNumber(const std::string& str);
    static std::vector<std::string> Split(const std::string& str, char delimiter);
};