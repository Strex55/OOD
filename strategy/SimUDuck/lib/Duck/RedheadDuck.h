#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"
#include "Dance/IDanceBehavior.h"

#include <memory>

class RedheadDuck : public Duck, IDanceBehavior
{
public:
	RedheadDuck()
		: Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}

	void Dance() override
	{
		std::cout << "I`m dancing menuet!" << std::endl;
	}

};

#endif
