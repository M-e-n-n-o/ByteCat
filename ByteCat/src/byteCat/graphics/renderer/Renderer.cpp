#include "bcpch.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	namespace Graphics
	{
		#define CHECK_INIT if(!s_isInit) { LOG_ERROR("The renderer has not been initialized yet!"); return; }

		void Renderer::SetAPI(const GraphicsAPI& api)
		{
			if (s_graphicsAPI == GraphicsAPI::None)
			{
				s_graphicsAPI = api;
			}
		}

		void Renderer::Init()
		{
			if (s_graphicsAPI == GraphicsAPI::None)
			{
				LOG_ERROR("Set the graphics API before initializing the renderer!");
				return;
			}

			if (!s_isInit)
			{
				s_rendererAPI = RendererAPI::Create(s_graphicsAPI);
				s_isInit = true;
			}
		}

		void Renderer::SetSubmissionRenderer(SubmissionRenderer* renderer)
		{
			if (renderer == nullptr)
			{
				delete renderer;
				return;
			}

			if (!s_isInit)
			{
				LOG_ERROR("Initialize the renderer before setting the submission renderer!");
				delete renderer;
				return;
			}

			if (!renderer->supports(s_graphicsAPI))
			{
				LOG_ERROR("Submission renderer: {0} does not support the selected graphics API!", renderer->getName());
				delete renderer;
				return;
			}

			delete s_submissionRenderer;
			s_submissionRenderer = renderer;
			s_submissionRenderer->init(s_rendererAPI);

			s_hasSubmissionRenderer = true;
		}

		void Renderer::Shutdown()
		{
			delete s_rendererAPI;
			delete s_submissionRenderer;
		}

		void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
		{
			CHECK_INIT

			s_rendererAPI->setViewport(x, y, width, height);
		}

		void Renderer::Submit(const Renderable& renderable)
		{
			CHECK_INIT

			if (!s_hasSubmissionRenderer)
			{
				LOG_ERROR("No submission renderer has been set!");
				return;
			}

			s_submissionRenderer->submit(renderable);
		}

		void Renderer::SetSceneData(const SceneData& sceneData)
		{
			CHECK_INIT

			if (!s_hasSubmissionRenderer)
			{
				LOG_ERROR("No submission renderer has been set!");
				return;
			}

			s_submissionRenderer->setSceneData(sceneData);
		}

		void Renderer::RenderSubmissions()
		{
			CHECK_INIT

			if (!s_hasSubmissionRenderer)
			{
				return;
			}

			s_submissionRenderer->renderSubmissions();
		}
	}
}
