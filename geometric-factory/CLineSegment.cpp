#include "CLineSegment.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor)
    : m_start(start), m_end(end), m_outlineColor(outlineColor) {}

CPoint CLineSegment::GetStartPoint() const 
{
    return m_start; 
}
CPoint CLineSegment::GetEndPoint() const 
{
    return m_end; 
}

double CLineSegment::GetArea() const 
{
    return 0.0; 
}

double CLineSegment::GetPerimeter() const 
{
    double dx = m_end.GetX() - m_start.GetX();
    double dy = m_end.GetY() - m_start.GetY();
    return std::sqrt(dx * dx + dy * dy);
}

uint32_t CLineSegment::GetOutlineColor() const { return m_outlineColor; }

std::string CLineSegment::ToString() const 
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << "Line Segment:\n"
        << "  Start: (" << m_start.GetX() << ", " << m_start.GetY() << ")\n"
        << "  End: (" << m_end.GetX() << ", " << m_end.GetY() << ")";
    return oss.str();
}