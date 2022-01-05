#pragma once
#include "glm/vec4.hpp"
#include "byteCat/graphics/entity/VertexArray.h"

namespace BC
{
	enum class GraphicsAPI
	{
		None = 0,
		OpenGL = 1
	};

	class RendererAPI
	{
	private:
		static GraphicsAPI graphicsAPI;
	
	public:
		virtual ~RendererAPI() = default;
			
		virtual void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void clearColor(const glm::vec4& color) = 0;
		virtual void clearBuffers() = 0;
		virtual void Draw(VertexArray* vao, unsigned int indexCount = 0) = 0;
		
		static GraphicsAPI& GetAPI() { return graphicsAPI; }
		static RendererAPI* Create(const GraphicsAPI& api);
	};
}
