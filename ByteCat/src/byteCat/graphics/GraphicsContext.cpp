#include "bcpch.h"
#include "byteCat/graphics/GraphicsContext.h"
#include "byteCat/graphics/renderer/Renderer.h"

#include "platform/openGL/OpenGLGraphicsContext.h"

namespace BC
{
	namespace Graphics
	{
		GraphicsContext* GraphicsContext::Create(void* window)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!");		return nullptr;
			case GraphicsAPI::OpenGL:	LOG_INFO("Detected OpenGL as Graphics API");	return new Platform::OpenGLGraphicsContext((GLFWwindow*)window);
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
