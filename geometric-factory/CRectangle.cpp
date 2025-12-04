#include "CRectangle.h"
#include <sstream>
#include <iomanip>

CRectangle::CRectangle(
    const CPoint& leftTop,
    double width,
    double height,
    uint32_t outlineColor,
    uint32_t fillColor
)
    : m_leftTop(leftTop)
    , m_width(width)
    , m_height(height)
    , m_outlineColor(outlineColor)
    , m_fillColor(fillColor) {}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
    return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

std::string CRectangle::ToString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << "Rectangle:\n"
        << "  LeftTop: (" << m_leftTop.GetX() << ", " << m_leftTop.GetY() << ")\n"
        << "  RightBottom: (" << (m_leftTop.GetX() + m_width) << ", "
        << (m_leftTop.GetY() + m_height) << ")\n"
        << "  Width: " << m_width << "\n"
        << "  Height: " << m_height;
    return oss.str();
}