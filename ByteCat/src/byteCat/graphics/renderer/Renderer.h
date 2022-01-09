#pragma once
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RenderData.h"
#include "byteCat/graphics/renderer/RendererBase.h"

namespace BC
{	
	/// <summary>
	/// This abstraction of the renderer holds the active renderer
	/// and GraphicsAPI. After telling this class to render something it will
	/// direct the request through to the active renderer.
	/// </summary>
	class Renderer
	{
	private:
		// inline static std::vector<RendererCommand> renderCommands;
		//
		// inline static bool renderFrame = false;
		// inline static std::vector<Renderable> submittedRenderables;
		// inline static SceneData sceneData;
		
		inline static bool isInit = false;
		// inline static bool shouldShutdown = false;
		
		inline static RenderBase* activeRenderer = nullptr;

		inline static GraphicsAPI graphicsAPI = GraphicsAPI::None;
		inline static RendererAPI* rendererAPI = nullptr;

	public:
		static void SetAPI(const GraphicsAPI& api);
		static GraphicsAPI& GetAPI() { return graphicsAPI; }
		
		static void Init(RenderBase* renderer);

		// static void Run(Window* window);
		
		static void Shutdown();

		
		// ---------- Commands ----------
		
		static void Submit(const Renderable& renderable);
		static void RenderFrame(const SceneData& sceneData);
		
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	};
}
