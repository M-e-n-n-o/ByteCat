#include "bcpch.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"

#include "platform/CommandExecutor.h"

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

	void SimpleRenderer::renderFrame(const SceneData& sceneData)
	{
		Platform::CommandExecutor::PushCommand([this, &sceneData]()
		{
			m_rendererAPI->clearBuffers();
			m_rendererAPI->clearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

			for (const auto& entity : m_entities)
			{
				entity.shader->bind();
				entity.vao->bind();
				m_rendererAPI->draw(entity.vao);
			}

			m_entities.clear();
		});
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
