#include "bcpch.h"
#include "byteCat/graphics/renderers/Renderer.h"

namespace BC
{
	#define CHECK_INIT if(!isInit) return;


	void Renderer::SetAPI(const GraphicsAPI& api)
	{
		if (graphicsAPI == GraphicsAPI::None)
		{
			graphicsAPI = api;
		}
	}
	
	void Renderer::Init(RenderBase* renderer)
	{		
		if (renderer == nullptr)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(graphicsAPI))
		{
			LOG_WARN("Selected renderer does not support the selected graphics API!");
			delete renderer;
			return;
		}

		if (!isInit)
		{
			isInit = true;

			activeRenderer = renderer;
			rendererAPI = RendererAPI::Create(graphicsAPI);
		}
	}

	void Renderer::Shutdown()
	{
		delete rendererAPI;
		delete activeRenderer;
	}

	void Renderer::StartScene(const SceneData& sceneData)
	{
		CHECK_INIT
		
		activeRenderer->startScene(rendererAPI, sceneData);
	}

	void Renderer::Submit(const Renderable& renderable)
	{
		CHECK_INIT
		
		activeRenderer->submit(renderable);
	}

	void Renderer::RenderScene()
	{
		CHECK_INIT
		
		activeRenderer->renderScene();
	}

	void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
	{
		CHECK_INIT

		rendererAPI->setViewport(x, y, width, height);
	}

	void Renderer::SetRenderer(RenderBase* renderer)
	{
		if (!isInit)
		{
			delete renderer;
			return;
		}
		
		if (renderer == nullptr)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(graphicsAPI))
		{
			LOG_WARN("Selected renderer does not support the selected graphics API!");
			delete renderer;
			return;
		}

		delete activeRenderer;
		activeRenderer = renderer;
	}
}
