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

	void onEvent(Event& event) override
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<KeyPressedEvent>(BC_BIND_EVENT_FN(onKey));
	}

	bool onKey(KeyPressedEvent& event)
	{
		LOG_INFO("Key: {0}", event.getKeyCode() == KeyCode::A);
		return true;
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