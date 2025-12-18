#ifndef GEOM_VISUALIZER_PARSER_H
#define GEOM_VISUALIZER_PARSER_H

#include "Geometry.h"
#include <memory>
#include <vector>
#include <string>

namespace geom
{

    class Parser
    {
    public:
        Parser() = default;
        std::vector<std::shared_ptr<IGeometry>> ParseFile(const std::string& path) const;
        static int WriteResults(const std::string& path, const std::vector<std::shared_ptr<IGeometry>>& shapes);

    private:
        static std::shared_ptr<IGeometry> ParseLine(const std::string& line);
        static int ReadPoint(const std::string& src, const std::string& key, Point& out);
        static int ReadInt(const std::string& src, const std::string& key, int& out);
        static std::string Normalize(const std::string& s);
    };

} 

#endif