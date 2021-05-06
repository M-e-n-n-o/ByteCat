#include <ByteCat.h>
#include <iostream>

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
		BC_INFO(Input::IsKeyPressed(KeyCode::A));
	}

	void render() override
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