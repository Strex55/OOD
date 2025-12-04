#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape 
{
public:
    CTriangle(
        const CPoint& vertex1,
        const CPoint& vertex2,
        const CPoint& vertex3,
        uint32_t outlineColor,
        uint32_t fillColor
    );

    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;

private:
    CPoint m_vertex1;
    CPoint m_vertex2;
    CPoint m_vertex3;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};