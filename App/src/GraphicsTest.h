#pragma once
#include <ByteCat.h>

using namespace BC;
using namespace App;
using namespace Inputs;

class CustomEvent : public Event
{
public:
	CustomEvent() = default;
	
	EventType getEventType() const override { return EventType::Other; }
	const char* getName() const override { return "Custom event"; }
	int getCategoryFlags() const override { return EventCatApplication; }
};

class CustomEventCallback : public EventCallback
{
public:
	CustomEventCallback(void(* callback)(const Event&))
		: EventCallback(callback)
	{
		
	}

	bool operator==(const Event& event) const override
	{
		if (const CustomEvent* e = dynamic_cast<const CustomEvent*>(&event); e != nullptr)
		{
			return true;
		}

		return false;
	}
};

class GraphicsTest : public Layer
{
	std::shared_ptr<Texture2D> texture;

	int id0;
	int id1;
	int id2;

public:
	static void test(const Event& event)
	{
		const KeyEvent* keyEvent = static_cast<const KeyEvent*>(&event);
		
		if (keyEvent->getKeyCode() == KeyCode::A)
		{
			LOG_INFO("a");
		} else if (keyEvent->getKeyCode() == KeyCode::W)
		{
			LOG_INFO("w");
		}
	}

	static void test2(const Event& event)
	{
		LOG_INFO("jaa");
	}
	
	GraphicsTest() : Layer("Graphics Test")
	{
		texture = Texture2D::Create("wall.jpg");

		// Input<>::AddCustomKeyCode("jump", KeyCode::Space);
		// Input<>::AddCustomKeyCode("jump", KeyCode::S);
		// Input<>::AddCustomKeyCode("jump", MouseCode::ButtonLeft);
		// Input<>::AddCustomKeyCode("jump", GamepadButton::A);
		
		//id0 = Input::StartListening(new MouseCallback(EventType::MouseScrolled, test2));
		//id0 = Input<>::StartListening(new CustomEventCallback(test2));
		
		// id1 = Input<>::StartListening(new KeyCallback(KeyCode::W, test));
		// id2 = Input<>::StartListening(new KeyCallback(KeyCode::A, test));
	}

	void onUpdate() override
	{		
		Renderer2D::Clear({ 1, 0, 0, 1 });

		// Renderer2D::SetColor({ 1, 1, 1, 1 });
		// Renderer2D::DrawImage({ 0, 0 }, 0, { 1, 1 }, texture);
		
		Renderer2D::SetColor({ 0, 1, 0, 1 });
		Renderer2D::DrawRectangle({ 0, 0 }, 10, { 1, 1 });

		// if (Input<>::IsPressed("jump"))
		// {
		// 	LOG_INFO("Jump");
		// }
		//
		// if (Input<>::IsPressed(KeyCode::K))
		// {
		// 	Input<>::StopListening(id1);
		// }
	}

	void onGuiRender() override
	{
		// ImGui::ShowDemoWindow();

		// ImGui::Begin("Test");
		// ImGui::Text("Hoi");
		// ImGui::End();
	}

	void onEvent(Event& event) override
	{
		// Input<>::HandleEvent(CustomEvent());
	}
};