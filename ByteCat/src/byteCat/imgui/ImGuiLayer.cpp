#include "bcpch.h"
#include "byteCat/imgui/ImGuiLayer.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLImGuiRenderer.h"

namespace BC
{
	ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer")
	{
		m_renderer = ImGuiRenderer::Create();
	}

	void ImGuiLayer::begin()
	{
		m_renderer->begin();
	}

	void ImGuiLayer::end()
	{
		m_renderer->end();
	}

	void ImGuiLayer::onAttach()
	{
		m_renderer->enable();
	}

	void ImGuiLayer::onDetach()
	{
		m_renderer->disable();
	}

	std::shared_ptr<ImGuiRenderer> ImGuiRenderer::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLImGuiRenderer>();
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
