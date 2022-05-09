#pragma once
#include <ByteCat.h>

using namespace BC;
using namespace App;

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
	
	GraphicsTest() : Layer("UserLayer")
	{
		texture = Texture2D::Create("wall.jpg");

		Input::AddCustomKeyCode("jump", KeyCode::Space);

		id0 = Input::StartListening(new MouseCallback(EventType::MouseScrolled, test2));
		
		id1 = Input::StartListening(new KeyCallback(KeyCode::W, test));
		id2 = Input::StartListening(new KeyCallback(KeyCode::A, test));
	}

	void onUpdate() override
	{		
		Renderer::Clear({ 1, 0, 0, 1 });

		Renderer::SetColor({ 1, 1, 1, 1 });
		Renderer::DrawImage({ 1, 0 }, 0, { 1, 1 }, texture);
		
		Renderer::SetColor({ 0, 1, 0, 1 });
		Renderer::DrawRectangle({ -1, 0 }, 10, { 1, 1 });

		if (Input::IsKeyPressed("jump"))
		{
			LOG_INFO("Jump");
		}

		if (Input::IsKeyPressed(KeyCode::K))
		{
			Input::StopListening(id1);
		}
	}

	void onGuiRender() override
	{
		ImGui::ShowDemoWindow();
	}
};