#include "Parser.h"
#include "TriangleAdapter.h"
#include "RectangleAdapter.h"
#include "CircleAdapter.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

namespace geom {

static std::string trim(const std::string& s) {
  const auto first = s.find_first_not_of(" \t\r\n");
  if (first == std::string::npos) return "";
  const auto last = s.find_last_not_of(" \t\r\n");
  return s.substr(first, last - first + 1);
}

std::string Parser::normalize(const std::string& s) {
  std::string out;
  out.reserve(s.size());
  for (char c : s) {
    if (c == ',') out.push_back(',');
    else if (std::isspace(static_cast<unsigned char>(c))) continue;
    else out.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
  }
  return out;
}

bool Parser::readPoint(const std::string& src, const std::string& key, Point& out) {
  const std::regex rx(key + R"(\s*[:=]\s*(-?\d+)\s*,\s*(-?\d+))", std::regex::icase);
  std::smatch m;
  if (std::regex_search(src, m, rx) && m.size() == 3) {
    out.x = std::stoi(m[1].str());
    out.y = std::stoi(m[2].str());
    return true;
  }
  return false;
}

bool Parser::readInt(const std::string& src, const std::string& key, int& out) {
  const std::regex rx(key + R"(\s*[:=]\s*(-?\d+))", std::regex::icase);
  std::smatch m;
  if (std::regex_search(src, m, rx) && m.size() == 2) {
    out = std::stoi(m[1].str());
    return true;
  }
  return false;
}

std::unique_ptr<IGeometry> Parser::parseLine(const std::string& rawLine) {
  const std::string line = trim(rawLine);
  if (line.empty()) return nullptr;

  auto upperLine = line;
  std::transform(upperLine.begin(), upperLine.end(), upperLine.begin(),
                 [](unsigned char c){ return static_cast<char>(std::toupper(c)); });

  if (upperLine.rfind("TRIANGLE", 0) == 0) {
    Point p1{}, p2{}, p3{};
    if (readPoint(line, "P1", p1) && readPoint(line, "P2", p2) && readPoint(line, "P3", p3)) {
      return std::make_unique<TriangleAdapter>(p1, p2, p3);
    }
  } else if (upperLine.rfind("RECTANGLE", 0) == 0) {
    Point p1{}, p2{};
    if (readPoint(line, "P1", p1) && readPoint(line, "P2", p2)) {
      return std::make_unique<RectangleAdapter>(p1, p2);
    }
  } else if (upperLine.rfind("CIRCLE", 0) == 0) {
    Point c{};
    int r{};
    if (readPoint(line, "C", c) && readInt(line, "R", r)) {
      return std::make_unique<CircleAdapter>(c, r);
    }
  }

  return nullptr;
}

std::vector<std::unique_ptr<IGeometry>> Parser::parseFile(const std::string& path) const {
  std::ifstream in(path);
  std::vector<std::unique_ptr<IGeometry>> result;
  if (!in) return result;

  std::string line;
  while (std::getline(in, line)) {
    auto shape = parseLine(line);
    if (shape) result.push_back(std::move(shape));
  }
  return result;
}

void Parser::writeResults(const std::string& path, const std::vector<std::unique_ptr<IGeometry>>& shapes) {
  std::ofstream out(path, std::ios::trunc);
  for (const auto& s : shapes) {
    out << s->toOutputString() << "\n";
  }
}

}  