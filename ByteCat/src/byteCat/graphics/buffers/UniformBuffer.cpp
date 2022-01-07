#include "bcpch.h"
#include "byteCat/graphics/buffers/UniformBuffer.h"
#include "byteCat/graphics/renderers/Renderer.h"
#include "platform/openGL/OpenGLUniformBuffer.h"

namespace BC
{
	std::shared_ptr<UniformBuffer> UniformBuffer::Create(const std::string& blockName, unsigned bindingIndex)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLUniformBuffer>(blockName, bindingIndex);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
