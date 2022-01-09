#include "bcpch.h"
#include "byteCat/graphics/renderer/Renderer.h"

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
			LOG_WARN("{0} does not support the selected graphics API!", renderer->getName());
			delete renderer;
			return;
		}

		if (!isInit)
		{
			isInit = true;

			activeRenderer = renderer;
			rendererAPI = RendererAPI::Create(graphicsAPI);
			activeRenderer->init(rendererAPI);
		}
	}

	// void Renderer::Run(Window* window)
	// {
	// 	CHECK_INIT
	// 	
	// 	while (!shouldShutdown)
	// 	{
	// 		window->update();
	// 		
	// 		if (window->isMinimized())
	// 		{
	// 			continue;
	// 		}
	// 		
	// 		if (!renderCommands.empty())
	// 		{
	// 			for (auto& command : renderCommands)
	// 			{
	// 				command.execute(rendererAPI);
	// 			}
	// 		}
	//
	// 		if (renderFrame)
	// 		{
	// 			
	// 		}
	// 	}
	//
	// 	delete rendererAPI;
	// 	delete activeRenderer;
	// }

	void Renderer::Shutdown()
	{
		delete rendererAPI;
		delete activeRenderer;
	}

	void Renderer::Submit(const Renderable& renderable)
	{
		CHECK_INIT
		
		activeRenderer->submit(renderable);
		// submittedRenderables.push_back(renderable);
	}

	void Renderer::RenderFrame(const SceneData& sceneData)
	{
		CHECK_INIT

		activeRenderer->renderFrame(sceneData);

		// renderFrame = true;
		// sceneData = data;
	}

	void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
	{
		CHECK_INIT

		rendererAPI->setViewport(x, y, width, height);
		// renderCommands.push_back(SetViewPortCommand(x, y, width, height));
	}
}
