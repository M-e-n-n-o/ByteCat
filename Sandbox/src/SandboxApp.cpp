#include <ByteCat.h>

using namespace BC;

class ExampleLayer : public Layer
{	
public:
	ExampleLayer() : Layer("ExampleLayer")
	{

	}

	void onUpdate() override
	{		

	}
};


class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	// The end of your application
	~Sandbox() override
	{

	}
};

Application* BC::CreateApplication()
{
	return new Sandbox();
}