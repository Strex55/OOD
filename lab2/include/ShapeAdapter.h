#ifndef GEOM_VISUALIZER_SHAPE_ADAPTER_H
#define GEOM_VISUALIZER_SHAPE_ADAPTER_H

#include "Geometry.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace geom
{

	class ShapeAdapter : public IGeometry
	{
	public:
		~ShapeAdapter() override = default;

		void draw(sf::RenderTarget& target) const override;
		sf::FloatRect getBounds() const override;
		void moveBy(float dx, float dy) override;

	protected:
		explicit ShapeAdapter(std::unique_ptr<sf::Shape> shape);

		void setStyle(const sf::Color& fill, const sf::Color& outline, float outlineThickness);

		const sf::Shape& shape() const { return *shape_; }
		sf::Shape& shape() { return *shape_; }

		std::unique_ptr<sf::Shape> shape_;
	};

}

#endif