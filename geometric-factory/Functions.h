#pragma once
#include <memory>
#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>
#include "IShape.h"
#include "Constants.h"
#include "ShapeFactory.h"

bool PrintShapeInfo(const IShape& shape);
IShape* MaxArea(const std::vector<std::unique_ptr<IShape>>& shapes);
IShape* MinPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes);