#include <ByteCat.h>

class Sandbox : public ByteCat::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

ByteCat::Application* ByteCat::createApplication()
{
	return new Sandbox();
}