#include <memory>

using namespace std;

struct IQuackBehavior
{
	virtual void Quack() = 0;
	virtual ~IQuackBehavior() {}
};

struct IFlyBehavior
{
	virtual void Fly() = 0;
	virtual ~IFlyBehavior() {}
};

struct IDanceBehavior
{
	virtual void const Dance() = 0;
	virtual ~IDanceBehavior() {}
};

class CDuck
{
public:
	void PerformQuack()
	{
		m_quackBehavior->Quack();
	}

	void PerformFly()
	{
		m_flyBehavior->Fly();
	}

	void PerformDance()
	{
		m_danceBehavior->Dance();
	}

protected:
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class CQuack : public IQuackBehavior
{
public:
	void Quack() override {}
};

class CFlyWithWings : public IFlyBehavior
{
public:
	void Fly() override {}
};

class CDance : public IDanceBehavior
{
public:
	void const Dance() override {}
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
	{
		m_quackBehavior = make_unique<CQuack>();
		m_flyBehavior = make_unique<CFlyWithWings>();
		m_danceBehavior = make_unique<CDance>();
	}
};

int main()
{

}