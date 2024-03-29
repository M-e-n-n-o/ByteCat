#pragma once
#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "byteCat/graphics/renderer/RendererAPI.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLRendererAPI : public Graphics::RendererAPI
		{
		public:
			OpenGLRendererAPI();
			~OpenGLRendererAPI() = default;
			
			void setViewport(unsigned x, unsigned y, unsigned width, unsigned height) override;
			void clearColor(const glm::vec4& color) override;
			void clearBuffers() override;
			void draw(std::shared_ptr<Graphics::VertexArray> vao, unsigned indexCount) override;

		private:
			void setDepthTest(bool enable) override;
			void setCullingMode(const Graphics::CullingMode& mode) override;
		};
	}
}
#endif