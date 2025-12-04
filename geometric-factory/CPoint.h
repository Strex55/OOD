#pragma once

class CPoint 
{
public:
    CPoint(double x, double y);
    double GetX() const;
    double GetY() const;
private:
    double m_x;
    double m_y;
}; 