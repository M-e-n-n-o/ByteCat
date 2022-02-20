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
		m_entities.push_back(renderable);
	}

	void SimpleRenderer::setSceneData(const SceneData& sceneData)
	{
		m_sceneData = sceneData;
	}

	void SimpleRenderer::renderFrame()
	{
		m_rendererAPI->clearBuffers();
		m_rendererAPI->clearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

		for (const auto& entity : m_entities)
		{
			entity.shader->bind();
			entity.shader->loadMatrix4("modelMatrix", entity.modelMatrix);
			entity.shader->loadMatrix4("viewMatrix", m_sceneData.viewMatrix);
			entity.shader->loadMatrix4("projectionMatrix", m_sceneData.projectionMatrix);
			
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
			
			m_rendererAPI->draw(entity.vao);
		}

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
