#include "bcpch.h"
#include "byteCat/graphics/buffers/ArrayBuffer.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLArrayBuffer.h"

namespace BC
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(unsigned size)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLVertexBuffer>(size);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned size)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLVertexBuffer>(vertices, size);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(unsigned* indices, unsigned count)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLIndexBuffer>(indices, count);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
