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
		BC_INFO("Update");
	}

	void onRender() override
	{
		BC_INFO("Render");
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