#pragma once
#include <memory>
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/Renderable.h"
#include "byteCat/graphics/renderer/CameraData.h"
#include "byteCat/graphics/renderer/RenderPass.h"
#include "byteCat/graphics/renderer/LightingData.h"

namespace BC
{
	namespace Graphics
	{
		/**
		 * @brief
		 * This abstraction of the renderer holds the active renderer
		 * and GraphicsAPI. After telling this class to render something it will
		 * direct the request through to the submission renderer.
		 * 
		 * To draw simple 2D geometry without much hassle it is recommended to use the Renderer2D
		 */
		class Renderer
		{
		private:
			inline static bool s_isInit = false;

			inline static GraphicsAPI s_graphicsAPI = GraphicsAPI::None;
			inline static RendererAPI* s_rendererAPI = nullptr;

			inline static std::vector<std::shared_ptr<RenderPass>> s_renderPasses;
			inline static std::vector<std::shared_ptr<Renderable>> s_renderables;
			inline static std::shared_ptr<CameraData> s_cameraData = nullptr;
			inline static std::shared_ptr<LightingData> s_lightingData = nullptr;

		public:
			static void SetAPI(const GraphicsAPI& api);
			static GraphicsAPI& GetAPI() { return s_graphicsAPI; }

			static void Init();
			static RendererAPI* GetRenderer() { return s_rendererAPI; }

			static void Shutdown();

			static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

			static void Submit(const std::shared_ptr<RenderPass>& renderPass);
			static void Submit(const std::shared_ptr<Renderable>& renderable);
			static void Submit(const std::shared_ptr<CameraData>& cameraData);
			static void Submit(const std::shared_ptr<LightingData>& lightingData);

			static void Render();
		};
	}
}
