#pragma once
#include <ByteCat.h>

using namespace BC;
using namespace App;

class GraphicsTest : public Layer
{
	std::shared_ptr<Texture2D> texture;
	
public:
	GraphicsTest() : Layer("UserLayer")
	{
		texture = Texture2D::Create("wall.jpg");
	}

	void onUpdate() override
	{
		Renderer::Clear({ 1, 0, 0, 1 });

		Renderer::SetColor({ 1, 1, 1, 1 });
		Renderer::DrawImage({ 1, 0 }, 0, { 1, 1 }, texture);
		
		Renderer::SetColor({ 0, 1, 0, 1 });
		Renderer::DrawRectangle({ -1, 0 }, 10, { 1, 1 });
	}

	void onGuiRender() override
	{
		ImGui::ShowDemoWindow();
	}
};