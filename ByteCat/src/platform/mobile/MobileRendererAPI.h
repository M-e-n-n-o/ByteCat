#pragma once
#ifdef BC_PLATFORM_MOBILE
#include "byteCat/graphics/renderer/RendererAPI.h"

namespace BC
{
	namespace Platform
	{
		class MobileRendererAPI : public Graphics::RendererAPI
		{
		public:
			MobileRendererAPI();
			~MobileRendererAPI() = default;

			void setViewport(unsigned x, unsigned y, unsigned width, unsigned height) override;
			void clearColor(const glm::vec4& color) override;
			void clearBuffers() override;
			void draw(std::shared_ptr<Graphics::VertexArray> vao, unsigned indexCount) override;

		private:
			void setCullingMode(const Graphics::CullingMode& mode) override;
		};
	}
}
#endif