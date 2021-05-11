#include <ByteCat.h>

using namespace BC;

class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox()
	{
		 
	}

	void update() override
	{
		
	}

	// The end of your application
	~Sandbox()
	{

	}
};

Application* BC::CreateApplication()
{
	return new Sandbox();
}