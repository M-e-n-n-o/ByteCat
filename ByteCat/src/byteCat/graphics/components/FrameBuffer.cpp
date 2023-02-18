#include "bcpch.h"
#include "byteCat/graphics/components/FrameBuffer.h"
#include "byteCat/graphics/renderer/Renderer.h"

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
	#include "platform/openGL/OpenGLFrameBuffer.h"
#endif

namespace BC
{
	namespace Graphics
	{
		std::shared_ptr<FrameBuffer> FrameBuffer::Create(const std::string& name, unsigned width, unsigned height)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:			LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
			case GraphicsAPI::OpenGL:
			case GraphicsAPI::OpenGLES:		return std::make_shared<Platform::OpenGLFrameBuffer>(name, width, height);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
