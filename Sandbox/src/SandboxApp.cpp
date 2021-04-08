#include <ByteCat.h>

class Sandbox : public ByteCat::Application
{
public:
	// The init of your application
	Sandbox()
	{
		
	}

	// The end of your application
	~Sandbox()
	{

	}
};

ByteCat::Application* ByteCat::CreateApplication()
{
	return new Sandbox();
}