#include "bcpch.h"
#include "byteCat/graphics/renderers/SimpleRenderer.h"

namespace BC
{
	void SimpleRenderer::startScene(RendererAPI* rendererAPI, const SceneData& sceneData)
	{
		this->rendererAPI = rendererAPI;
		this->sceneData = sceneData;

		rendererAPI->clearBuffers();
		rendererAPI->clearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	}

	void SimpleRenderer::submit(const Renderable& renderable)
	{		
		auto shader = renderable.shader;
		
		shader->bind();
		
		renderable.vao->bind();
		rendererAPI->draw(renderable.vao);
	}

	void SimpleRenderer::renderScene()
	{
		
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
