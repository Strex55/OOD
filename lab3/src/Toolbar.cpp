#include "Toolbar.h"
#include "Application.h"
#include "StateFactory.h"
#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>

namespace geom {

void Toolbar::loadFont() {
    if (!font_.openFromFile("arial.ttf")) {
        std::cerr << "Warning: Failed to load font 'arial.ttf'. Text may not display properly." << std::endl;
        if (!font_.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
            std::cerr << "Failed to load system font as well." << std::endl;
        }
    }
}

Toolbar::Toolbar(Application& app) : app_(app) {
  loadFont();
  
  background_.setSize(sf::Vector2f(1000.0f, TOOLBAR_HEIGHT));
  background_.setPosition(sf::Vector2f(0, 0));
  background_.setFillColor(sf::Color(240, 240, 240));
  background_.setOutlineColor(sf::Color(200, 200, 200));
  background_.setOutlineThickness(1.0f);

  // Available colors: Black, Red, Green, Blue, Yellow
  availableColors_ = {
    sf::Color::Black,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow
  };

  // Available thicknesses: 1, 2, 3
  availableThicknesses_ = {1.0f, 2.0f, 3.0f};

  // Tool labels
  std::vector<std::string> toolNames = {"Select", "Fill", "Tri", "Rect", "Circle"};
  
  // Initialize tool buttons (Select, Fill, Add Triangle, Add Rectangle, Add Circle)
  const int numTools = 5;
  toolButtons_.resize(numTools);
  toolLabels_.clear();
  toolLabels_.reserve(numTools);
  
  for (int i = 0; i < numTools; ++i) {
    toolButtons_[i].setSize(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE));
    toolButtons_[i].setPosition(sf::Vector2f(
      BUTTON_SPACING + i * (BUTTON_SIZE + BUTTON_SPACING),
      BUTTON_SPACING
    ));
    toolButtons_[i].setFillColor(sf::Color(220, 220, 220));
    toolButtons_[i].setOutlineColor(sf::Color::Black);
    toolButtons_[i].setOutlineThickness(1.0f);
    
    // Create label text - SFML 3 requires font in constructor
    // Always use the font we tried to load (even if empty, SFML 3 may handle it)
    toolLabels_.emplace_back(font_, toolNames[i], 12);
    toolLabels_[i].setFillColor(sf::Color::Black);
    
    // Center text on button - SFML 3 uses position/size instead of left/top/width/height
    const auto btnPos = toolButtons_[i].getPosition();
    const auto btnSize = toolButtons_[i].getSize();
    const auto textBounds = toolLabels_[i].getLocalBounds();
    toolLabels_[i].setPosition(sf::Vector2f(
      btnPos.x + (btnSize.x - textBounds.size.x) / 2.0f - textBounds.position.x,
      btnPos.y + (btnSize.y - textBounds.size.y) / 2.0f - textBounds.position.y
    ));
  }

  // Initialize color buttons
  colorButtons_.resize(availableColors_.size());
  const float colorStartX = numTools * (BUTTON_SIZE + BUTTON_SPACING) + 20.0f;
  for (size_t i = 0; i < availableColors_.size(); ++i) {
    colorButtons_[i].setSize(sf::Vector2f(BUTTON_SIZE * 0.7f, BUTTON_SIZE * 0.7f));
    colorButtons_[i].setPosition(sf::Vector2f(
      colorStartX + static_cast<float>(i) * (BUTTON_SIZE * 0.7f + BUTTON_SPACING),
      BUTTON_SPACING * 2.0f
    ));
    colorButtons_[i].setFillColor(availableColors_[i]);
    colorButtons_[i].setOutlineColor(sf::Color::Black);
    colorButtons_[i].setOutlineThickness(1.0f);
  }

  // Initialize thickness buttons
  thicknessButtons_.resize(availableThicknesses_.size());
  thicknessLabels_.clear();
  thicknessLabels_.reserve(availableThicknesses_.size());
  const float thicknessStartX = colorStartX + availableColors_.size() * (BUTTON_SIZE * 0.7f + BUTTON_SPACING) + 20.0f;
  for (size_t i = 0; i < availableThicknesses_.size(); ++i) {
    thicknessButtons_[i].setSize(sf::Vector2f(BUTTON_SIZE * 0.7f, BUTTON_SIZE * 0.7f));
    thicknessButtons_[i].setPosition(sf::Vector2f(
      thicknessStartX + static_cast<float>(i) * (BUTTON_SIZE * 0.7f + BUTTON_SPACING),
      BUTTON_SPACING * 2.0f
    ));
    thicknessButtons_[i].setFillColor(sf::Color(180, 180, 180));
    thicknessButtons_[i].setOutlineColor(sf::Color::Black);
    thicknessButtons_[i].setOutlineThickness(1.0f);
    
    // Create thickness label - SFML 3 requires font in constructor
    std::string thicknessStr = std::to_string(static_cast<int>(availableThicknesses_[i]));
    // Always use the font we tried to load
    thicknessLabels_.emplace_back(font_, thicknessStr, 12);
    thicknessLabels_[i].setFillColor(sf::Color::Black);
    
    // Center text on button - SFML 3 uses position/size
    const auto btnPos = thicknessButtons_[i].getPosition();
    const auto btnSize = thicknessButtons_[i].getSize();
    const auto textBounds = thicknessLabels_[i].getLocalBounds();
    thicknessLabels_[i].setPosition(sf::Vector2f(
      btnPos.x + (btnSize.x - textBounds.size.x) / 2.0f - textBounds.position.x,
      btnPos.y + (btnSize.y - textBounds.size.y) / 2.0f - textBounds.position.y
    ));
  }
}

void Toolbar::draw(sf::RenderTarget& target) {
  target.draw(background_);

  // Draw tool buttons with labels
  for (size_t i = 0; i < toolButtons_.size(); ++i) {
    if (i == static_cast<size_t>(selectedToolIndex_)) {
      toolButtons_[i].setOutlineColor(sf::Color::Blue);
      toolButtons_[i].setOutlineThickness(2.0f);
    } else {
      toolButtons_[i].setOutlineColor(sf::Color::Black);
      toolButtons_[i].setOutlineThickness(1.0f);
    }
    target.draw(toolButtons_[i]);
    // Draw label
    if (i < toolLabels_.size()) {
      target.draw(toolLabels_[i]);
    }
  }

  // Draw color buttons
  for (size_t i = 0; i < colorButtons_.size(); ++i) {
    if (i == static_cast<size_t>(selectedColorIndex_)) {
      colorButtons_[i].setOutlineColor(sf::Color::Blue);
      colorButtons_[i].setOutlineThickness(2.0f);
    } else {
      colorButtons_[i].setOutlineColor(sf::Color::Black);
      colorButtons_[i].setOutlineThickness(1.0f);
    }
    target.draw(colorButtons_[i]);
  }

  // Draw thickness buttons
  for (size_t i = 0; i < thicknessButtons_.size(); ++i) {
    if (i == static_cast<size_t>(selectedThicknessIndex_)) {
      thicknessButtons_[i].setOutlineColor(sf::Color::Blue);
      thicknessButtons_[i].setOutlineThickness(2.0f);
    } else {
      thicknessButtons_[i].setOutlineColor(sf::Color::Black);
      thicknessButtons_[i].setOutlineThickness(1.0f);
    }
    target.draw(thicknessButtons_[i]);
    // Draw label
    if (i < thicknessLabels_.size()) {
      target.draw(thicknessLabels_[i]);
    }
  }
}

void Toolbar::HandleClick(const sf::Vector2f& pos)
{
    // Check tool buttons (State Pattern switching)
    for (size_t i = 0; i < m_toolButtons.size(); ++i)
    {
        const auto& btn = m_toolButtons[i];
        const auto btnPos = btn.getPosition();
        const auto btnSize = btn.getSize();

        if (pos.x >= btnPos.x && pos.x <= btnPos.x + btnSize.x &&
            pos.y >= btnPos.y && pos.y <= btnPos.y + btnSize.y)
        {
            m_selectedToolIndex = static_cast<int>(i);
            EditorMode mode = EditorMode::Select;

            // Use switch-case instead of if-else
            switch (i)
            {
            case 0: mode = EditorMode::Select; break;
            case 1: mode = EditorMode::Fill; break;
            case 2: mode = EditorMode::AddTriangle; break;
            case 3: mode = EditorMode::AddRectangle; break;
            case 4: mode = EditorMode::AddCircle; break;
            }

            m_app.SetState(StateFactory::CreateState(mode, m_app));
            return;
        }
    }

    // Check color buttons
    for (size_t i = 0; i < m_colorButtons.size(); ++i)
    {
        const auto& btn = m_colorButtons[i];
        const auto btnPos = btn.getPosition();
        const auto btnSize = btn.getSize();

        if (pos.x >= btnPos.x && pos.x <= btnPos.x + btnSize.x &&
            pos.y >= btnPos.y && pos.y <= btnPos.y + btnSize.y)
        {
            m_selectedColorIndex = static_cast<int>(i);
            sf::Color selectedColor = Constants::AVAILABLE_COLORS[i];

            if (m_app.GetCurrentMode() == EditorMode::Fill)
            {
                // For fill mode, change fill color with undo
                auto& selected = m_app.GetSelected();
                if (!selected.empty())
                {
                    std::vector<std::shared_ptr<IGeometry>> shapesToChange;
                    shapesToChange.reserve(selected.size());

                    for (auto& shape : selected)
                    {
                        shapesToChange.push_back(shape);
                    }

                    auto cmd = std::make_unique<ChangeStyleCommand>(
                        std::move(shapesToChange),
                        selected[0]->GetFillColor(),      
                        selectedColor,                    
                        selected[0]->GetOutlineColor(),   
                        selected[0]->GetOutlineColor(),   
                        selected[0]->GetOutlineThickness(), 
                        selected[0]->GetOutlineThickness()  
                    );

                    m_app.ExecuteCommand(std::move(cmd));
                }
                m_app.SetFillColor(selectedColor);
            }
            else
            {
                // For other modes, change outline color with undo
                auto& selected = m_app.GetSelected();
                if (!selected.empty())
                {
                    std::vector<std::shared_ptr<IGeometry>> shapesToChange;
                    shapesToChange.reserve(selected.size());

                    for (auto& shape : selected)
                    {
                        shapesToChange.push_back(shape);
                    }

                    auto cmd = std::make_unique<ChangeStyleCommand>(
                        std::move(shapesToChange),
                        selected[0]->GetFillColor(),      
                        selected[0]->GetFillColor(),      
                        selected[0]->GetOutlineColor(),   
                        selectedColor,                    
                        selected[0]->GetOutlineThickness(),
                        selected[0]->GetOutlineThickness() 
                    );

                    m_app.ExecuteCommand(std::move(cmd));
                }
                m_app.SetOutlineColor(selectedColor);
            }
            return;
        }
    }

    // Check thickness buttons
    for (size_t i = 0; i < m_thicknessButtons.size(); ++i)
    {
        const auto& btn = m_thicknessButtons[i];
        const auto btnPos = btn.getPosition();
        const auto btnSize = btn.getSize();

        if (pos.x >= btnPos.x && pos.x <= btnPos.x + btnSize.x &&
            pos.y >= btnPos.y && pos.y <= btnPos.y + btnSize.y)
        {
            m_selectedThicknessIndex = static_cast<int>(i);
            float thickness = Constants::AVAILABLE_THICKNESSES[i];

            // Apply thickness with undo
            auto& selected = m_app.GetSelected();
            if (!selected.empty())
            {
                std::vector<std::shared_ptr<IGeometry>> shapesToChange;
                shapesToChange.reserve(selected.size());

                for (auto& shape : selected)
                {
                    shapesToChange.push_back(shape);
                }

                auto cmd = std::make_unique<ChangeStyleCommand>(
                    std::move(shapesToChange),
                    selected[0]->GetFillColor(),      
                    selected[0]->GetFillColor(),      
                    selected[0]->GetOutlineColor(),   
                    selected[0]->GetOutlineColor(),   
                    selected[0]->GetOutlineThickness(), 
                    thickness                         
                );

                m_app.ExecuteCommand(std::move(cmd));
            }
            m_app.SetOutlineThickness(thickness);
            return;
        }
    }
}

sf::FloatRect Toolbar::getBounds() const {
  return sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1000.0f, TOOLBAR_HEIGHT));
}

}  