#pragma once
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RenderData.h"
#include "byteCat/graphics/renderer/BaseRenderer.h"

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
		inline static bool s_isInit = false;
		
		inline static BaseRenderer* s_activeRenderer = nullptr;

		inline static GraphicsAPI s_graphicsAPI = GraphicsAPI::None;
		inline static RendererAPI* s_rendererAPI = nullptr;

	public:
		static void SetAPI(const GraphicsAPI& api);
		static GraphicsAPI& GetAPI() { return s_graphicsAPI; }
		
		static void Init(BaseRenderer* renderer);
		static void SetRenderer(BaseRenderer* renderer);
		
		static void Shutdown();
		
		// ---------- Commands ----------
		
		static void Submit(const Renderable& renderable);
		static void RenderFrame(const SceneData& sceneData);
		
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	};
}
