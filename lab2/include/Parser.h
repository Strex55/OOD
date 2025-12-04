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
		std::vector<std::shared_ptr<IGeometry>> parseFile(const std::string& path) const;
		static void writeResults(const std::string& path, const std::vector<std::shared_ptr<IGeometry>>& shapes);

	private:
		static std::shared_ptr<IGeometry> parseLine(const std::string& line);
		static bool readPoint(const std::string& src, const std::string& key, Point& out);
		static bool readInt(const std::string& src, const std::string& key, int& out);
		static std::string normalize(const std::string& s);
	};

}

#endif