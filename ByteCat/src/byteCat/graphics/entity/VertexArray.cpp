#include "bcpch.h"
#include "byteCat/graphics/entity/VertexArray.h"
#include "byteCat/graphics/renderers/Renderer.h"
#include "platform/openGL/OpenGLVertexArray.h"

namespace BC
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return new Platform::OpenGLVertexArray();
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
