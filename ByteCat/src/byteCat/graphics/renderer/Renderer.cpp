#include "bcpch.h"
#include "byteCat/graphics/renderer/Renderer.h"

namespace BC
{
	#define CHECK_INIT if(!s_isInit) return;

	void Renderer::SetAPI(const GraphicsAPI& api)
	{
		if (s_graphicsAPI == GraphicsAPI::None)
		{
			s_graphicsAPI = api;
		}
	}
	
	void Renderer::Init(BaseRenderer* renderer)
	{		
		if (renderer == nullptr)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(s_graphicsAPI))
		{
			LOG_WARN("{0} does not support the selected graphics API!", renderer->getName());
			delete renderer;
			return;
		}

		if (!s_isInit)
		{
			s_isInit = true;

			s_activeRenderer = renderer;
			s_rendererAPI = RendererAPI::Create(s_graphicsAPI);
			s_activeRenderer->init(s_rendererAPI);
		}
	}

	void Renderer::SetRenderer(BaseRenderer* renderer)
	{
		if (renderer == nullptr || !s_isInit)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(s_graphicsAPI))
		{
			LOG_WARN("{0} does not support the selected graphics API!", renderer->getName());
			delete renderer;
			return;
		}

		delete s_activeRenderer;
		s_activeRenderer = renderer;
		s_activeRenderer->init(s_rendererAPI);
	}

	void Renderer::Shutdown()
	{
		delete s_rendererAPI;
		delete s_activeRenderer;
	}

	void Renderer::Submit(const Renderable& renderable)
	{
		CHECK_INIT
		
		s_activeRenderer->submit(renderable);
	}

	void Renderer::RenderFrame(const SceneData& sceneData)
	{
		CHECK_INIT

		s_activeRenderer->renderFrame(sceneData);
	}

	void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
	{
		CHECK_INIT

		s_rendererAPI->setViewport(x, y, width, height);
	}
}
