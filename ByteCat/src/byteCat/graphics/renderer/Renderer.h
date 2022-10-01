#pragma once
#include <memory>
#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RendererInput.h"
#include "byteCat/graphics/renderer/SubmissionRenderer.h"
#include "byteCat/graphics/renderer/RendererInput.h"

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
			inline static bool s_hasSubmissionRenderer = false;

			inline static SubmissionRenderer* s_submissionRenderer = nullptr;

			inline static GraphicsAPI s_graphicsAPI = GraphicsAPI::None;
			inline static RendererAPI* s_rendererAPI = nullptr;

		public:
			static void SetAPI(const GraphicsAPI& api);
			static GraphicsAPI& GetAPI() { return s_graphicsAPI; }

			static void Init();
			static RendererAPI* GetRenderer() { return s_rendererAPI; }
			
			static void SetSubmissionRenderer(SubmissionRenderer* renderer);

			static void Shutdown();

			static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

			// Submission renderer commands
			static void Submit(const std::shared_ptr<RendererInput>& input);
			static void Render();
		};
	}
}
