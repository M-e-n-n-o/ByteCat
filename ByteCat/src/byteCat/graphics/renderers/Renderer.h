#pragma once
#include "byteCat/graphics/renderers/RendererAPI.h"
#include "byteCat/graphics/entity/RenderData.h"

namespace BC
{
	// Inherit from this class to create a custom Renderer
	class RenderBase
	{
	public:
		virtual ~RenderBase() = default;
		
		virtual void startScene(RendererAPI* rendererAPI, const SceneData& sceneData) = 0;
		virtual void submit(const Renderable& renderable) = 0;
		virtual void renderScene() = 0;

		virtual bool supports(const GraphicsAPI& api) = 0;
	};
	
	class Renderer
	{
	private:
		inline static bool isInit = false;
		
		inline static RenderBase* activeRenderer = nullptr;

		inline static GraphicsAPI graphicsAPI = GraphicsAPI::None;
		inline static RendererAPI* rendererAPI = nullptr;

	public:
		static void SetAPI(const GraphicsAPI& api);
		static void Init(RenderBase* renderer);
		static void Shutdown();

		static void StartScene(const SceneData& sceneData);
		static void Submit(const Renderable& renderable);
		static void RenderScene();
		
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		
		static void SetRenderer(RenderBase* renderer);
		static GraphicsAPI& GetAPI() { return graphicsAPI; }
	};
}
