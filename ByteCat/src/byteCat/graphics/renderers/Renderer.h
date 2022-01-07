#pragma once
#include "byteCat/graphics/renderers/RendererAPI.h"
#include "byteCat/graphics/buffers/RenderData.h"

namespace BC
{
	/// <summary>
	/// Inherit from this class to create a custom Renderer. Apply this
	/// renderer in the renderer class using the SetRenderer() method.
	/// </summary>
	class RenderBase
	{
	public:
		virtual ~RenderBase() = default;
		
		virtual void startScene(RendererAPI* rendererAPI, const SceneData& sceneData) = 0;
		virtual void setSceneData(const SceneData& sceneData) = 0;
		virtual void submit(const Renderable& renderable) = 0;
		virtual void renderScene() = 0;

		virtual const std::string& getName() const = 0;

		virtual bool supports(const GraphicsAPI& api) = 0;
	};

	/// <summary>
	/// This abstraction of the renderer holds the active renderer
	/// and GraphicsAPI. After telling this class to render something it will
	/// direct the request through to the active renderer.
	/// </summary>
	class Renderer
	{
	private:
		inline static bool isInit = false;
		
		inline static RenderBase* activeRenderer = nullptr;

		inline static GraphicsAPI graphicsAPI = GraphicsAPI::None;
		inline static RendererAPI* rendererAPI = nullptr;

	public:
		/// <summary>
		/// Set the GraphicsAPI of the renderer (this can only be set once).
		/// Call this method before the Init of this class and creating the window.
		/// </summary>
		/// <param name="api">The GraphicsAPI the renderer should use</param>
		static void SetAPI(const GraphicsAPI& api);

		/// <summary>
		/// Initializes the renderer. Call this method after the SetAPI() method
		/// and before creating the window.
		/// </summary>
		/// <param name="renderer"></param>
		static void Init(RenderBase* renderer);

		static void Shutdown();

		static void StartScene(const SceneData& sceneData);
		static void SetSceneData(const SceneData& sceneData);
		static void Submit(const Renderable& renderable);
		static void RenderScene();
		
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		
		static void SetRenderer(RenderBase* renderer);
		static GraphicsAPI& GetAPI() { return graphicsAPI; }
	};
}
