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
		inline static bool s_hasRenderer = false;
		
		inline static BaseRenderer* s_activeRenderer = nullptr;

		inline static GraphicsAPI s_graphicsAPI = GraphicsAPI::None;
		inline static RendererAPI* s_rendererAPI = nullptr;

	public:
		static void SetAPI(const GraphicsAPI& api);
		static GraphicsAPI& GetAPI() { return s_graphicsAPI; }
		
		static void Init(BaseRenderer* renderer);
		static void SetRenderer(BaseRenderer* renderer);
		
		static void Shutdown();

		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		
		// Renderer basic commands
		static void Clear(const glm::vec3& color);
		static void SetColor(const glm::vec4& color);
		static void DrawRectangle(const glm::vec3& position, const glm::vec3& scale);
		static void DrawImage(const glm::vec3& position, const glm::vec3& scale, std::shared_ptr<Texture2D> texture);
		
		// Base renderer commands
		static void Submit(const Renderable& renderable);
		static void SetSceneData(const SceneData& sceneData);
		static void RenderSubmissions();
	};
}
