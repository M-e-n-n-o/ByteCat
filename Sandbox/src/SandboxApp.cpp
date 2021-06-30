#include <ByteCat.h>

using namespace BC;


class ExampleLayer : public BC::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer")
	{
		
	}

	void onUpdate() override
	{

	}

	void onEvent(Event& event) override
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
		pushOverlay(new ImGuiLayer());
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