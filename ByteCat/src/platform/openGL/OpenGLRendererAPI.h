#pragma once
#include "byteCat/graphics/renderer/RendererAPI.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLRendererAPI : public RendererAPI
		{
		public:
			OpenGLRendererAPI();
			~OpenGLRendererAPI() = default;
			
			void setViewport(unsigned x, unsigned y, unsigned width, unsigned height) override;
			void clearColor(const glm::vec4& color) override;
			void clearBuffers() override;
			void draw(std::shared_ptr<VertexArray> vao, unsigned indexCount) override;
		};
	}
}
