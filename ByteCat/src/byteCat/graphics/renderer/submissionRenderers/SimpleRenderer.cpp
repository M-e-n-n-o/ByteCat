#include "bcpch.h"
#include "byteCat/graphics/renderer/submissionRenderers/SimpleRenderer.h"

namespace BC
{
	namespace Graphics
	{
		void SimpleRenderer::init(RendererAPI* rendererAPI)
		{
			this->m_rendererAPI = rendererAPI;
		}

		void SimpleRenderer::submit(const std::shared_ptr<RendererInput>& input)
		{
			switch (input->getInputType())
			{
			case RendererInput::InputType::Renderable:
				{
					auto renderable = std::dynamic_pointer_cast<Renderable>(input);
					m_entities.push_back(renderable);
					break;
				}

			case RendererInput::InputType::CameraData:
				{
					auto cameraData = std::dynamic_pointer_cast<CameraData>(input);
					m_cameraData = cameraData;
					break;
				}
			}
		}

		void SimpleRenderer::renderSubmissions()
		{
			m_rendererAPI->clearColor(glm::vec4(0.69, 1, 1, 1));
			m_rendererAPI->clearBuffers();

			for (int i = 0; i < m_entities.size(); i++)
			{
				auto entity = m_entities[i];
				entity->shader->bind();
				entity->shader->loadMatrix4("_modelMatrix", entity->modelMatrix);
				entity->shader->loadMatrix4("_viewMatrix", m_cameraData->viewMatrix);
				entity->shader->loadMatrix4("_projectionMatrix", m_cameraData->projectionMatrix);

				int unit = 0;
				for (auto& texture : entity->textures)
				{
					texture->bind(unit++);
				}

				entity->vao->bind();

				if (entity->onRender != nullptr)
				{
					entity->onRender(entity);
				}

				RendererAPI::SetCullingMode(entity->cullingMode);

				m_rendererAPI->draw(entity->vao);
			}

			m_entities.clear();
		}

		bool SimpleRenderer::supports(const GraphicsAPI& api)
		{
			switch (api)
			{
			case GraphicsAPI::None:		return false;
			case GraphicsAPI::OpenGL:	return true;
			case GraphicsAPI::OpenGLES:	return true;
			}

			return false;
		}
	}
}
