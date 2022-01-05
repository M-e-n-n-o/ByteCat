#pragma once
#include "byteCat/graphics/renderers/RendererAPI.h"
#include "byteCat/graphics/entity/Shader.h"

namespace BC
{
	// Inherit from this class to create a custom Renderer
	class RenderBase
	{
	public:
		virtual ~RenderBase() = default;
		
		virtual void startScene() = 0;
		virtual void submit(VertexArray* vao, Shader* shader) = 0;
		virtual void renderScene() = 0;

		virtual bool supports(const GraphicsAPI& api) = 0;
	};
	
	class Renderer
	{
	private:
		static bool isInit;
		
		static RenderBase* activeRenderer;
	
	protected:
		static RendererAPI* rendererAPI;

	public:
		static void Create(RenderBase* renderer, const GraphicsAPI& api);
		static void Shutdown();

		static void StartScene();
		static void Submit(VertexArray* vao, Shader* shader);
		static void RenderScene();
		
		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
		
		static void SetRenderer(RenderBase* renderer);
		static GraphicsAPI& GetAPI() { return RendererAPI::GetAPI(); }
	};
}
