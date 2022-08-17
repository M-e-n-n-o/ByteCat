#include "bcpch.h"
#include "byteCat/graphics/GraphicsContext.h"
#include "byteCat/graphics/renderer/Renderer.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
	#include "platform/openGL/OpenGLGraphicsContext.h"
#endif

namespace BC
{
	namespace Graphics
	{
		GraphicsContext* GraphicsContext::Create(void* window)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!");		return nullptr;

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
			case GraphicsAPI::OpenGL:	LOG_INFO("Detected OpenGL as Graphics API");	return new Platform::OpenGLGraphicsContext((GLFWwindow*)window);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
