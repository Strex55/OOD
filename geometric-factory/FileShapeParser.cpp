#include "FileShapeParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::vector<ShapeData> FileShapeParser::ParseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<ShapeData> shapes;
    std::string line;

    while (std::getline(file, line)) {
        // Пропускаем пустые строки
        if (line.empty()) continue;

        try {
            ShapeData shapeData = ParseLine(line);
            shapes.push_back(shapeData);
        }
        catch (const std::exception& e) {
            // Пропускаем строки с ошибками, продолжаем парсинг
            continue;
        }
    }

    return shapes;
}

ShapeData FileShapeParser::ParseLine(const std::string& line) {
    ShapeData data;

    // Находим разделитель типа и параметров
    size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) {
        throw std::runtime_error("Invalid format: missing colon");
    }

    // Извлекаем тип фигуры
    data.type = line.substr(0, colonPos);

    // Убираем пробелы в типе
    data.type.erase(std::remove_if(data.type.begin(), data.type.end(), ::isspace), data.type.end());

    // Обрабатываем параметры после двоеточия
    std::string paramsStr = line.substr(colonPos + 1);

    if (data.type == "TRIANGLE") {
        // TRIANGLE: P1=100,100; P2=200,200; P3=150,150
        auto parts = Split(paramsStr, ';');
        if (parts.size() != 3) {
            throw std::runtime_error("Triangle must have exactly 3 points");
        }

        for (const auto& part : parts) {
            size_t equalsPos = part.find('=');
            if (equalsPos == std::string::npos) {
                throw std::runtime_error("Invalid point format");
            }
            std::string pointStr = part.substr(equalsPos + 1);
            data.points.push_back(ParsePoint(pointStr));
        }
    }
    else if (data.type == "RECTANGLE") {
        // RECTANGLE: P1=200,200; P2=300,300
        auto parts = Split(paramsStr, ';');
        if (parts.size() != 2) {
            throw std::runtime_error("Rectangle must have exactly 2 points");
        }

        for (const auto& part : parts) {
            size_t equalsPos = part.find('=');
            if (equalsPos == std::string::npos) {
                throw std::runtime_error("Invalid point format");
            }
            std::string pointStr = part.substr(equalsPos + 1);
            data.points.push_back(ParsePoint(pointStr));
        }
    }
    else if (data.type == "CIRCLE") {
        // CIRCLE: C=100,100; R=50
        auto parts = Split(paramsStr, ';');
        if (parts.size() != 2) {
            throw std::runtime_error("Circle must have center and radius");
        }

        // Центр
        size_t equalsPos = parts[0].find('=');
        if (equalsPos == std::string::npos) {
            throw std::runtime_error("Invalid center format");
        }
        std::string centerStr = parts[0].substr(equalsPos + 1);
        data.points.push_back(ParsePoint(centerStr));

        // Радиус
        equalsPos = parts[1].find('=');
        if (equalsPos == std::string::npos) {
            throw std::runtime_error("Invalid radius format");
        }
        std::string radiusStr = parts[1].substr(equalsPos + 1);
        data.radius = ParseNumber(radiusStr);
    }
    else {
        throw std::runtime_error("Unknown shape type: " + data.type);
    }

    return data;
}

sf::Vector2f FileShapeParser::ParsePoint(const std::string& pointStr) {
    // Убираем пробелы
    std::string cleanStr = pointStr;
    cleanStr.erase(std::remove_if(cleanStr.begin(), cleanStr.end(), ::isspace), cleanStr.end());

    auto coords = Split(cleanStr, ',');
    if (coords.size() != 2) {
        throw std::runtime_error("Point must have exactly 2 coordinates");
    }

    float x = ParseNumber(coords[0]);
    float y = ParseNumber(coords[1]);

    return sf::Vector2f(x, y);
}

float FileShapeParser::ParseNumber(const std::string& str) {
    try {
        return std::stof(str);
    }
    catch (const std::exception&) {
        throw std::runtime_error("Invalid number format: " + str);
    }
}

std::vector<std::string> FileShapeParser::Split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        // Убираем пробелы по краям
        item.erase(0, item.find_first_not_of(' '));
        item.erase(item.find_last_not_of(' ') + 1);
        if (!item.empty()) {
            result.push_back(item);
        }
    }

    return result;
}