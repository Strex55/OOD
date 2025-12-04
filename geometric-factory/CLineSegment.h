#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : public IShape 
{
public:
    CLineSegment(const CPoint& start, const CPoint& end, uint32_t outlineColor);

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;

private:
    CPoint m_start;
    CPoint m_end;
    uint32_t m_outlineColor;
};