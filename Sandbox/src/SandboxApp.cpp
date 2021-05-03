#include <ByteCat.h>

class Sandbox : public ByteCat::Application
{
public:
	// The init of your application
	Sandbox()
	{

	}

	void onUpdate() override
	{
		
	}

	void onRender() override
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