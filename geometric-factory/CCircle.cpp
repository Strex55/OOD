#include "CCircle.h"
#include "Constants.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CCircle::CCircle(
    const CPoint& center,
    double radius,
    uint32_t outlineColor,
    uint32_t fillColor
)
    : m_center(center)
    , m_radius(radius)
    , m_outlineColor(outlineColor)
    , m_fillColor(fillColor)
{
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}

double CCircle::GetRadius() const
{
    return m_radius;
}

double CCircle::GetArea() const
{
    return Constants::PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * Constants::PI * m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

std::string CCircle::ToString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << "Circle:\n"
        << "  Center: (" << m_center.GetX() << ", " << m_center.GetY() << ")\n"
        << "  Radius: " << m_radius;
    return oss.str();
}