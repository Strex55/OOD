#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"
#include "Dance/IDanceBehavior.h"

class MallardDuck : public Duck, IDanceBehavior
{
public:
	MallardDuck()
		: Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}

	void Dance() override 
	{
		std::cout << "I`m dancing valse!" << std::endl;
	}
};

#endif
