#include "ShapeAdapter.h"

namespace geom
{

	ShapeAdapter::ShapeAdapter(std::unique_ptr<sf::Shape> shape)
		: shape_(std::move(shape))
	{
	}

	void ShapeAdapter::setStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness)
	{
		shape_->setFillColor(fill);
		shape_->setOutlineColor(outline);
		shape_->setOutlineThickness(outlineThickness);
	}

	void ShapeAdapter::draw(sf::RenderTarget& target) const
	{
		target.draw(*shape_);
	}

	sf::FloatRect ShapeAdapter::getBounds() const
	{
		return shape_->getGlobalBounds();
	}

	void ShapeAdapter::moveBy(float dx, float dy)
	{
		shape_->move(sf::Vector2f(dx, dy));
	}

}