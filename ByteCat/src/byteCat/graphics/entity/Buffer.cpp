#include "bcpch.h"
#include "byteCat/graphics/entity/Buffer.h"
#include "byteCat/graphics/renderers/Renderer.h"
#include "platform/openGL/OpenGLBuffer.h"

namespace BC
{
	VertexBuffer* VertexBuffer::Create(unsigned size)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return new Platform::OpenGLVertexBuffer(size);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned size)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return new Platform::OpenGLVertexBuffer(vertices, size);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(unsigned* indices, unsigned count)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return new Platform::OpenGLIndexBuffer(indices, count);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
