#include "bcpch.h"
#include "byteCat/graphics/renderers/Renderer.h"

namespace BC
{
	#define CHECK_INIT if(!isInit) return;
	
	bool Renderer::isInit = false;
	
	void Renderer::Create(RenderBase* renderer, const GraphicsAPI& api)
	{		
		if (renderer == nullptr)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(api))
		{
			LOG_WARN("Selected renderer does not support the selected graphics API!");
			delete renderer;
			return;
		}

		if (!isInit)
		{
			isInit = true;

			activeRenderer = renderer;
			rendererAPI = RendererAPI::Create(api);
		}
	}

	void Renderer::Shutdown()
	{
		delete rendererAPI;
		delete activeRenderer;
	}

	void Renderer::StartScene()
	{
		CHECK_INIT
		
		activeRenderer->startScene();
	}

	void Renderer::Submit(VertexArray* vao, Shader* shader)
	{
		CHECK_INIT
		
		activeRenderer->submit(vao, shader);
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

		if (!renderer->supports(RendererAPI::GetAPI()))
		{
			LOG_WARN("Selected renderer does not support the selected graphics API!");
			delete renderer;
			return;
		}

		delete activeRenderer;
		activeRenderer = renderer;
	}
}
