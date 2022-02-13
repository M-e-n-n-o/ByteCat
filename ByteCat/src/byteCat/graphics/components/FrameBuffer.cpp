#include "bcpch.h"
#include "byteCat/graphics/components/FrameBuffer.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLFrameBuffer.h"

namespace BC
{
	std::shared_ptr<FrameBuffer> FrameBuffer::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLFrameBuffer>();
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
