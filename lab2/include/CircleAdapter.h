#ifndef GEOM_VISUALIZER_CIRCLE_ADAPTER_H
#define GEOM_VISUALIZER_CIRCLE_ADAPTER_H

#include "ShapeAdapter.h"

namespace geom
{

	class CircleAdapter : public ShapeAdapter
	{
	public:
		CircleAdapter(const Point& center, int radius);
		~CircleAdapter() override = default;

		double getPerimeter() const override;
		double getArea() const override;
		std::string toOutputString() const override;
		bool containsPoint(const sf::Vector2f& point) const override;
		void moveBy(float dx, float dy) override;

	private:
		Point center_;
		int radius_;
	};

}

#endif