#include "CTriangle.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CTriangle::CTriangle(
    const CPoint& vertex1,
    const CPoint& vertex2,
    const CPoint& vertex3,
    uint32_t outlineColor,
    uint32_t fillColor
) : m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3),
m_outlineColor(outlineColor), m_fillColor(fillColor) {}

CPoint CTriangle::GetVertex1() const 
{ 
    return m_vertex1; 
}
CPoint CTriangle::GetVertex2() const 
{ 
    return m_vertex2; 
}
CPoint CTriangle::GetVertex3() const 
{
    return m_vertex3; 
}

double CTriangle::GetArea() const 
{
    return 0.5 * std::abs(
        (m_vertex2.GetX() - m_vertex1.GetX()) * (m_vertex3.GetY() - m_vertex1.GetY()) -
        (m_vertex3.GetX() - m_vertex1.GetX()) * (m_vertex2.GetY() - m_vertex1.GetY())
    );
}

double CTriangle::GetPerimeter() const 
{
    double dx12 = m_vertex2.GetX() - m_vertex1.GetX();
    double dy12 = m_vertex2.GetY() - m_vertex1.GetY();
    double a = std::sqrt(dx12 * dx12 + dy12 * dy12);

    double dx23 = m_vertex3.GetX() - m_vertex2.GetX();
    double dy23 = m_vertex3.GetY() - m_vertex2.GetY();
    double b = std::sqrt(dx23 * dx23 + dy23 * dy23);

    double dx31 = m_vertex1.GetX() - m_vertex3.GetX();
    double dy31 = m_vertex1.GetY() - m_vertex3.GetY();
    double c = std::sqrt(dx31 * dx31 + dy31 * dy31);

    return a + b + c;
}

uint32_t CTriangle::GetOutlineColor() const 
{
    return m_outlineColor; 
}
uint32_t CTriangle::GetFillColor() const 
{
    return m_fillColor; 
}

std::string CTriangle::ToString() const 
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << "Triangle:\n"
        << "  Vertex1: (" << m_vertex1.GetX() << ", " << m_vertex1.GetY() << ")\n"
        << "  Vertex2: (" << m_vertex2.GetX() << ", " << m_vertex2.GetY() << ")\n"
        << "  Vertex3: (" << m_vertex3.GetX() << ", " << m_vertex3.GetY() << ")";
    return oss.str();
}