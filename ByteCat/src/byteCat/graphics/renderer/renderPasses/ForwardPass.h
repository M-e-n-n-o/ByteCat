#pragma once
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RenderPass.h"

namespace BC
{
	namespace Graphics
	{
		class ForwardPass : public RenderPass
		{
		private:
			RendererAPI* m_rendererAPI;

		public:
			ForwardPass(): RenderPass("ForwardPass") {}

			void init(RendererAPI* rendererAPI) override
			{
				m_rendererAPI = rendererAPI;
			}

			void execute(std::vector<std::shared_ptr<Renderable>> renderables, std::shared_ptr<CameraData> cameraData, std::shared_ptr<LightingData> lightingData) override
			{
				m_rendererAPI->clearColor(glm::vec4(0.69, 1, 1, 1));
				m_rendererAPI->clearBuffers();

				for (const auto& renderable : renderables)
				{
					renderable->shader->bind();
					renderable->shader->loadMatrix4("_modelMatrix", renderable->modelMatrix);
					renderable->shader->loadMatrix4("_viewMatrix", cameraData->viewMatrix);
					renderable->shader->loadMatrix4("_projectionMatrix", cameraData->projectionMatrix);

					int unit = 0;
					for (auto& texture : renderable->textures)
					{
						texture->bind(unit++);
					}

					renderable->vao->bind();

					if (renderable->onRender != nullptr)
					{
						renderable->onRender(renderable);
					}

					RendererAPI::SetCullingMode(renderable->cullingMode);

					m_rendererAPI->draw(renderable->vao);
				}
			}
		};
	}
}