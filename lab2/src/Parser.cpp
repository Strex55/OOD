#include "Parser.h"
#include "TriangleAdapter.h"
#include "RectangleAdapter.h"
#include "CircleAdapter.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <iostream>

namespace geom
{

    static std::string trim(const std::string& s)
    {
        const auto first = s.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
        {
            return "";
        }
        const auto last = s.find_last_not_of(" \t\r\n");
        return s.substr(first, last - first + 1);
    }

    static std::string toUpper(const std::string& s)
    {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c) { return std::toupper(c); });
        return result;
    }

    enum class ShapeType
    {
        Unknown,
        Triangle,
        Rectangle,
        Circle
    };

    static ShapeType determineShapeType(const std::string& line)
    {
        std::string upperLine = toUpper(line);

        if (upperLine.rfind("TRIANGLE", 0) == 0)
        {
            return ShapeType::Triangle;
        }

        if (upperLine.rfind("RECTANGLE", 0) == 0)
        {
            return ShapeType::Rectangle;
        }

        if (upperLine.rfind("CIRCLE", 0) == 0)
        {
            return ShapeType::Circle;
        }

        return ShapeType::Unknown;
    }

    bool Parser::readPoint(const std::string& src, const std::string& key, Point& out)
    {
        const std::regex rx(key + R"(\s*[:=]\s*(-?\d+)\s*,\s*(-?\d+))", std::regex::icase);
        std::smatch m;

        if (std::regex_search(src, m, rx) && m.size() == 3)
        {
            out.x = std::stoi(m[1].str());
            out.y = std::stoi(m[2].str());
            return true;
        }

        return false;
    }

    bool Parser::readInt(const std::string& src, const std::string& key, int& out)
    {
        const std::regex rx(key + R"(\s*[:=]\s*(-?\d+))", std::regex::icase);
        std::smatch m;

        if (std::regex_search(src, m, rx) && m.size() == 2)
        {
            out = std::stoi(m[1].str());
            return true;
        }

        return false;
    }

    std::shared_ptr<IGeometry> Parser::parseLine(const std::string& rawLine)
    {
        const std::string line = trim(rawLine);

        if (line.empty())
        {
            return nullptr;
        }

        ShapeType type = determineShapeType(line);

        switch (type)
        {
        case ShapeType::Triangle:
        {
            Point p1{}, p2{}, p3{};

            if (readPoint(line, "P1", p1) &&
                readPoint(line, "P2", p2) &&
                readPoint(line, "P3", p3))
            {
                return std::make_shared<TriangleAdapter>(p1, p2, p3);
            }
            break;
        }

        case ShapeType::Rectangle:
        {
            Point p1{}, p2{};

            if (readPoint(line, "P1", p1) &&
                readPoint(line, "P2", p2))
            {
                return std::make_shared<RectangleAdapter>(p1, p2);
            }
            break;
        }

        case ShapeType::Circle:
        {
            Point center{};
            int radius{};

            if (readPoint(line, "C", center) &&
                readInt(line, "R", radius))
            {
                return std::make_shared<CircleAdapter>(center, radius);
            }
            break;
        }

        case ShapeType::Unknown:
        default:
            break;
        }

        return nullptr;
    }

    std::vector<std::shared_ptr<IGeometry>> Parser::parseFile(const std::string& path) const
    {
        std::ifstream in(path);
        std::vector<std::shared_ptr<IGeometry>> result;

        if (!in)
        {
            std::cerr << "Cannot open file: " << path << "\n";
            return result;
        }

        std::string line;
        while (std::getline(in, line))
        {
            auto shape = parseLine(line);
            if (shape)
            {
                result.push_back(shape);
            }
        }

        return result;
    }

    void Parser::writeResults(const std::string& path, const std::vector<std::shared_ptr<IGeometry>>& shapes)
    {
        std::ofstream out(path, std::ios::trunc);
        for (const auto& shape : shapes)
        {
            out << shape->toOutputString() << "\n";
        }
    }

} 