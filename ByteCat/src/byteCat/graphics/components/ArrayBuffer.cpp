#include "bcpch.h"
#include "byteCat/graphics/components/ArrayBuffer.h"
#include "byteCat/graphics/renderer/Renderer.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
	#include "platform/openGL/OpenGLArrayBuffer.h"
#endif

namespace BC
{
	namespace Graphics
	{
		std::shared_ptr<VertexBuffer> VertexBuffer::Create(unsigned size)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
			case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLVertexBuffer>(size);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}

		std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned size)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
			case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLVertexBuffer>(vertices, size);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}

		std::shared_ptr<IndexBuffer> IndexBuffer::Create(unsigned* indices, unsigned count)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
			case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLIndexBuffer>(indices, count);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
