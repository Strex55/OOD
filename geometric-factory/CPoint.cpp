#include "CPoint.h"

CPoint::CPoint(double x, double y)
    : m_x(x), m_y(y) {}

double CPoint::GetX() const 
{
    return m_x;
}

double CPoint::GetY() const 
{
    return m_y;
}