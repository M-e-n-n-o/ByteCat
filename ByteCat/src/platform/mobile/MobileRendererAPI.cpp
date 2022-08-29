#ifdef BC_PLATFORM_ANDROID
#include "bcpch.h"
#include <glfm.h>
#include "platform/mobile/MobileRendererAPI.h"

namespace BC
{
	namespace Platform
	{
		MobileRendererAPI::MobileRendererAPI()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		void MobileRendererAPI::setViewport(unsigned x, unsigned y, unsigned width, unsigned height)
		{
			glViewport(x, y, width, height);
		}

		void MobileRendererAPI::clearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void MobileRendererAPI::clearBuffers()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void MobileRendererAPI::draw(std::shared_ptr<Graphics::VertexArray> vao, unsigned indexCount)
		{
			unsigned int count = indexCount ? indexCount : vao->getIndexBuffer()->getCount();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}

		void MobileRendererAPI::setCullingMode(const Graphics::CullingMode& mode)
		{
			static Graphics::CullingMode currentMode = Graphics::CullingMode::Back;

			if (mode == currentMode)
			{
				return;
			}

			switch (mode)
			{
			case Graphics::CullingMode::None:			glDisable(GL_CULL_FACE); break;
			case Graphics::CullingMode::Front:			glEnable(GL_CULL_FACE); glCullFace(GL_FRONT); break;
			case Graphics::CullingMode::Back:			glEnable(GL_CULL_FACE); glCullFace(GL_BACK); break;
			case Graphics::CullingMode::FrontAndBack:	glEnable(GL_CULL_FACE); glCullFace(GL_FRONT_AND_BACK); break;
			}

			currentMode = mode;
		}
	}
}
#endif