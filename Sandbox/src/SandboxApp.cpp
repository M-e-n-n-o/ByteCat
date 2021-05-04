#include <ByteCat.h>

class Sandbox : public BC::Application
{
public:
	// The init of your application
	Sandbox()
	{
	
	}

	void update() override
	{
		
	}

	void render() override
	{

	}

	// The end of your application
	~Sandbox()
	{

	}
};

BC::Application* BC::CreateApplication()
{
	return new Sandbox();
}