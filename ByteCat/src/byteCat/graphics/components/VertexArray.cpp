#include "bcpch.h"
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/renderer/Renderer.h"

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
	#include "platform/openGL/OpenGLVertexArray.h"
#endif

namespace BC
{
	namespace Graphics
	{
		std::shared_ptr<VertexArray> VertexArray::Create()
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:			LOG_CRITICAL("No Graphics API selected!"); return nullptr;
				
#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
				case GraphicsAPI::OpenGL:
				case GraphicsAPI::OpenGLES:	return std::make_shared<Platform::OpenGLVertexArray>();
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
