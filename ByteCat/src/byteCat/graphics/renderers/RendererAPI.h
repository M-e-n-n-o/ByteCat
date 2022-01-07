#pragma once
#include "glm/vec4.hpp"
#include "byteCat/graphics/buffers/VertexArray.h"

namespace BC
{
	enum class GraphicsAPI
	{
		None = 0,
		OpenGL = 1
	};

	/// <summary>
	/// This generic RendererAPI directs requests to the native RendererAPI (for example: OpenGL)
	/// </summary>
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;
		
		virtual void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void clearColor(const glm::vec4& color) = 0;
		virtual void clearBuffers() = 0;
		virtual void draw(std::shared_ptr<VertexArray> vao, unsigned int indexCount = 0) = 0;
		
		static RendererAPI* Create(const GraphicsAPI& api);
	};
}
