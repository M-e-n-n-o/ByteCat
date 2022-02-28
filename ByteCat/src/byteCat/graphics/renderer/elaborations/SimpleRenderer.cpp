#include "bcpch.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"

namespace BC
{
	void SimpleRenderer::init(RendererAPI* rendererAPI)
	{
		this->m_rendererAPI = rendererAPI;
	}

	void SimpleRenderer::submit(const Renderable& renderable)
	{
		// switch (renderable.renderLayer)
		// {
		// case RenderLayer::Opaque:
		// 	{
		// 		m_entities.emplace(m_entities.begin() + m_transparentIndex, renderable);
		// 		m_transparentIndex++;
		// 		break;
		// 	}
		// case RenderLayer::Transparent:
		// 	{
				m_entities.push_back(renderable);
		// 		break;
		// 	}
		// }
	}

	void SimpleRenderer::setSceneData(const SceneData& sceneData)
	{
		m_sceneData = sceneData;
	}

	void SimpleRenderer::renderFrame()
	{
		m_rendererAPI->clearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
		m_rendererAPI->clearBuffers();

		for (int i = 0; i < m_entities.size(); i++)
		{
			const auto& entity = m_entities[i];
			entity.shader->bind();
			entity.shader->loadMatrix4("_modelMatrix", entity.modelMatrix);
			entity.shader->loadMatrix4("_viewMatrix", m_sceneData.viewMatrix);
			entity.shader->loadMatrix4("_projectionMatrix", m_sceneData.projectionMatrix);
			
			int unit = 0;
			for (auto& texture : entity.textures)
			{				
				texture->bind(unit++);
			}
			
			entity.vao->bind();

			if (entity.onRender != nullptr)
			{
				entity.onRender(entity);
			}

			RendererAPI::SetCullingMode(entity.cullingMode);
			
			m_rendererAPI->draw(entity.vao);
		}

		// m_transparentIndex = 0;
		m_entities.clear();
	}

	bool SimpleRenderer::supports(const GraphicsAPI& api)
	{
		switch (api)
		{
		case GraphicsAPI::None:		return false;
		case GraphicsAPI::OpenGL:	return true;
		}

		return false;
	}
}
