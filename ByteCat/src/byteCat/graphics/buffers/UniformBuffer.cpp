#include "bcpch.h"
#include "byteCat/graphics/buffers/UniformBuffer.h"
#include "byteCat/graphics/renderers/Renderer.h"
#include "platform/openGL/OpenGLUniformBuffer.h"

namespace BC
{
	// --------------------------------------------------------------------
	// ------------------------ UniformBuffer -----------------------------
	// --------------------------------------------------------------------
	
	std::shared_ptr<UniformBuffer> UniformBuffer::Create(const std::string& blockName, unsigned bindingIndex, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLUniformBuffer>(blockName, bindingIndex, size);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	std::shared_ptr<UniformBuffer> UniformBuffer::Create(const std::string& blockName, unsigned bindingIndex,
		unsigned size, const void* data)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLUniformBuffer>(blockName, bindingIndex, size, data);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	// --------------------------------------------------------------------
	// -------------------- UniformBuffer Builder -------------------------
	// --------------------------------------------------------------------

	UniformBuffer::Builder::Builder(const std::string& blockName, unsigned int bindingIndex)
	{
		buffer = Create(blockName, bindingIndex, MAX_BUFFER_SIZE);
	}

	UniformBuffer::Builder& UniformBuffer::Builder::addInt(const std::string& name, int value)
	{
		buffer->loadData(&value, sizeof(int), offset);
		offset += sizeof(int);
		
		return *this;
	}

	UniformBuffer::Builder& UniformBuffer::Builder::addFloat(const std::string& name, float value)
	{
		buffer->loadData(&value, sizeof(float), offset);
		offset += sizeof(float);

		return *this;
	}

	std::shared_ptr<UniformBuffer> UniformBuffer::Builder::build()
	{
		return buffer;
	}
}
