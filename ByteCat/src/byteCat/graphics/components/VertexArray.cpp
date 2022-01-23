#include "bcpch.h"
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLVertexArray.h"

namespace BC
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLVertexArray>();
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
