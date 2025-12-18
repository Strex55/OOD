#include "CompositeShape.h"
#include <algorithm>
#include <sstream>

namespace geom
{

    void CompositeShape::Add(const std::shared_ptr<IGeometry>& child)
    {
        m_children.push_back(child);
    }

    void CompositeShape::Remove(const std::shared_ptr<IGeometry>& child)
    {
        m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
    }

    double CompositeShape::GetPerimeter() const
    {
        double p = 0.0;
        for (const auto& c : m_children) p += c->GetPerimeter();
        return p;
    }

    double CompositeShape::GetArea() const
    {
        double s = 0.0;
        for (const auto& c : m_children) s += c->GetArea();
        return s;
    }

    void CompositeShape::Draw(sf::RenderTarget& target) const
    {
        for (const auto& c : m_children) c->Draw(target);
    }

    std::string CompositeShape::ToOutputString() const
    {
        std::ostringstream oss;
        oss << "GROUP: P=" << static_cast<long long>(std::llround(GetPerimeter()))
            << "; S=" << static_cast<long long>(std::llround(GetArea()));
        return oss.str();
    }

    bool CompositeShape::ContainsPoint(const sf::Vector2f& point) const
    {
        for (const auto& c : m_children)
        {
            if (c->ContainsPoint(point)) return true;
        }
        return false;
    }

    sf::FloatRect CompositeShape::GetBounds() const
    {
        if (m_children.empty()) return sf::FloatRect();

        auto b = m_children.front()->GetBounds();

        float left = b.position.x;
        float top = b.position.y;
        float right = b.position.x + b.size.x;
        float bottom = b.position.y + b.size.y;

        for (size_t i = 1; i < m_children.size(); ++i)
        {
            auto bi = m_children[i]->GetBounds();
            float biLeft = bi.position.x;
            float biTop = bi.position.y;
            float biRight = bi.position.x + bi.size.x;
            float biBottom = bi.position.y + bi.size.y;

            if (biLeft < left) left = biLeft;
            if (biTop < top) top = biTop;
            if (biRight > right) right = biRight;
            if (biBottom > bottom) bottom = biBottom;
        }

        return sf::FloatRect(sf::Vector2f(left, top), sf::Vector2f(right - left, bottom - top));
    }

    void CompositeShape::MoveBy(float dx, float dy)
    {
        for (const auto& c : m_children) c->MoveBy(dx, dy);
    }

    sf::Color CompositeShape::GetFillColor() const
    {
        if (m_children.empty())
        {
            return sf::Color::Transparent;
        }

        return m_children[0]->GetFillColor();
    }

    sf::Color CompositeShape::GetOutlineColor() const
    {
        if (m_children.empty())
        {
            return sf::Color::Transparent;
        }

        return m_children[0]->GetOutlineColor();
    }

    float CompositeShape::GetOutlineThickness() const
    {
        if (m_children.empty())
        {
            return 0.0f;
        }

        return m_children[0]->GetOutlineThickness();
    }

    void CompositeShape::SetFillColor(const sf::Color& color)
    {
        for (const auto& c : m_children) c->SetFillColor(color);
    }

    void CompositeShape::SetOutlineColor(const sf::Color& color)
    {
        for (const auto& c : m_children) c->SetOutlineColor(color);
    }

    void CompositeShape::SetOutlineThickness(float thickness)
    {
        for (const auto& c : m_children) c->SetOutlineThickness(thickness);
    }

}