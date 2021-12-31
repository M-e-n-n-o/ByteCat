#include <ByteCat.h>

using namespace BC;

class ExampleLayer : public Layer
{
	GamepadID controllerID;
	
	
public:
	ExampleLayer() : Layer("ExampleLayer")
	{
		auto gamepads = Input::GetActiveGamepads();
		LOG_INFO("Gamepad_1 name: {0}", gamepads[0].name);
		controllerID = gamepads[0].id;
	}

	void onUpdate() override
	{		
		float result = Input::GetGamepadAxis(GamepadAxis::LEFT_X, controllerID);
		LOG_INFO(result);
	}

	void onEvent(Event& event) override
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<KeyPressedEvent>(BC_BIND_EVENT_FN(onKey));
	}

	bool onKey(KeyPressedEvent& event)
	{
		LOG_INFO("Is key pressed A?: {0}", event.getKeyCode() == KeyCode::A);
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