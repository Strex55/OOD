#include "AddShapeState.h"
#include "Application.h"
#include "TriangleAdapter.h"
#include "RectangleAdapter.h"
#include "CircleAdapter.h"
#include "AddShapeCommand.h" 
#include "Geometry.h"
#include <memory>
#include <cmath>

namespace geom
{
    AddShapeState::AddShapeState(Application& app, EditorMode mode)
        : app_(app), mode_(mode), firstClick_(false), secondClick_(false), circleCenterSet_(false),
        p1_{ 0, 0 }, p2_{ 0, 0 }, p3_{ 0, 0 }, center_{ 0, 0 }, radius_(0)
    {
    }

    void AddShapeState::OnMousePress(const sf::Vector2f& pos)
    {
        if (mode_ == EditorMode::AddCircle)
        {
            if (!circleCenterSet_)
            {
                center_ = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                circleCenterSet_ = true;
            }
            else
            {
                int dx = static_cast<int>(pos.x) - center_.x;
                int dy = static_cast<int>(pos.y) - center_.y;
                radius_ = static_cast<int>(std::sqrt(dx * dx + dy * dy));
                if (radius_ < 5) radius_ = 5;

                Point c{ center_.x, center_.y };
                auto shape = std::make_shared<CircleAdapter>(c, radius_);
                shape->SetFillColor(app_.GetFillColor());
                shape->SetOutlineColor(app_.GetOutlineColor());
                shape->SetOutlineThickness(app_.GetOutlineThickness());

                // Используем команду для возможности отмены
                auto cmd = std::make_unique<AddShapeCommand>(app_, shape);
                app_.ExecuteCommand(std::move(cmd));

                circleCenterSet_ = false;
            }
        }
        else if (mode_ == EditorMode::AddRectangle)
        {
            if (!firstClick_)
            {
                p1_ = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                firstClick_ = true;
            }
            else
            {
                p2_ = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                Point p1{ p1_.x, p1_.y }, p2{ p2_.x, p2_.y };
                auto shape = std::make_shared<RectangleAdapter>(p1, p2);
                shape->SetFillColor(app_.GetFillColor());
                shape->SetOutlineColor(app_.GetOutlineColor());
                shape->SetOutlineThickness(app_.GetOutlineThickness());

                // Используем команду для возможности отмены
                auto cmd = std::make_unique<AddShapeCommand>(app_, shape);
                app_.ExecuteCommand(std::move(cmd));

                firstClick_ = false;
            }
        }
        else if (mode_ == EditorMode::AddTriangle)
        {
            if (!firstClick_)
            {
                p1_ = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                firstClick_ = true;
                secondClick_ = false;
            }
            else if (!secondClick_)
            {
                p2_ = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                secondClick_ = true;
            }
            else
            {
                p3_ = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                Point p1{ p1_.x, p1_.y }, p2{ p2_.x, p2_.y }, p3{ p3_.x, p3_.y };
                auto shape = std::make_shared<TriangleAdapter>(p1, p2, p3);
                shape->SetFillColor(app_.GetFillColor());
                shape->SetOutlineColor(app_.GetOutlineColor());
                shape->SetOutlineThickness(app_.GetOutlineThickness());

                // Используем команду для возможности отмены
                auto cmd = std::make_unique<AddShapeCommand>(app_, shape);
                app_.ExecuteCommand(std::move(cmd));

                firstClick_ = false;
                secondClick_ = false;
            }
        }
    }

    void AddShapeState::OnMouseMove(const sf::Vector2f& pos)
    {
        (void)pos; // Подавление предупреждения
    }

    void AddShapeState::OnMouseRelease(const sf::Vector2f& pos)
    {
        (void)pos; // Подавление предупреждения
    }

}