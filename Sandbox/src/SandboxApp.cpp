#include <ByteCat.h>
#include "imgui/imgui.h"

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

	void onImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void onEvent(Event& event) override
	{
		if (event.getEventType() == EventType::KeyPressed)
		{
			event.handled = true;
			KeyPressedEvent& e = (KeyPressedEvent&) event;
			if (e.getKeyCode() == KeyCode::Backspace)
			{
				LOG_INFO("Backspace is pressed");
				
			}
			LOG_INFO("{0}", (char)e.getKeyCode());
		}
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