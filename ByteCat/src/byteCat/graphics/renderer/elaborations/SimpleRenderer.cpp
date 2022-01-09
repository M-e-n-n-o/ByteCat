#include "bcpch.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"

namespace BC
{
	void SimpleRenderer::init(RendererAPI* rendererAPI)
	{
		this->rendererAPI = rendererAPI;
	}

	void SimpleRenderer::submit(const Renderable& renderable)
	{		
		entities.push_back(renderable);
	}

	void SimpleRenderer::renderFrame(const SceneData& sceneData)
	{
		rendererAPI->clearBuffers();
		rendererAPI->clearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

		for (const auto& entity : entities)
		{
			entity.shader->bind();
			entity.vao->bind();
			rendererAPI->draw(entity.vao);
		}
		
		entities.clear();
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
