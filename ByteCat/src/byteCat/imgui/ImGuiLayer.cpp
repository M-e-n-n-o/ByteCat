#include "bcpch.h"
#include "byteCat/imgui/ImGuiLayer.h"
#include "byteCat/graphics/renderer/Renderer.h"

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
	#include "platform/openGL/OpenGLImGuiRenderer.h"
#endif

namespace BC
{
	namespace Imgui
	{		
		ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
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
			switch (Graphics::Renderer::GetAPI())
			{
			case Graphics::GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
			case Graphics::GraphicsAPI::OpenGL:
			case Graphics::GraphicsAPI::OpenGLES:	return std::make_shared<Platform::OpenGLImGuiRenderer>();
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
