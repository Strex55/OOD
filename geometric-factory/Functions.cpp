#include "Functions.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

bool PrintShapeInfo(const IShape& shape) {
    std::cout << shape.ToString() << "\n";
    std::cout << "Area: " << std::fixed << std::setprecision(2) << shape.GetArea() << "\n";
    std::cout << "Perimeter: " << std::fixed << std::setprecision(2) << shape.GetPerimeter() << "\n";

    std::cout << "Outline color: #"
        << std::hex << std::setw(6) << std::setfill('0') << shape.GetOutlineColor()
        << std::dec << "\n";

    if (const ISolidShape* solid = dynamic_cast<const ISolidShape*>(&shape)) {
        std::cout << "Fill color: #"
            << std::hex << std::setw(6) << std::setfill('0') << solid->GetFillColor()
            << std::dec << "\n";
    }
    std::cout << std::endl;
    return true;
}

IShape* MaxArea(const std::vector<std::unique_ptr<IShape>>& shapes) {
    if (shapes.empty()) {
        return nullptr;
    }

    auto maxAreaIt = std::max_element(shapes.begin(), shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetArea() < b->GetArea();
        });

    return maxAreaIt->get();
}

IShape* MinPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes) {
    if (shapes.empty()) {
        return nullptr;
    }

    auto minPerimeterIt = std::min_element(shapes.begin(), shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetPerimeter() < b->GetPerimeter();
        });

    return minPerimeterIt->get();
}