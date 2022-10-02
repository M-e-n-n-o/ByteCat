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
			else
			{
				LOG_WARN("Cannot change the Graphics API after setting it the first time");
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

		void Renderer::Shutdown()
		{
			delete s_rendererAPI;
		}

		void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
		{
			CHECK_INIT

			s_rendererAPI->setViewport(x, y, width, height);
		}

		void Renderer::Submit(const std::shared_ptr<RenderPass>& renderPass)
		{
			CHECK_INIT

			LOG_INFO("Adding render pass: %s", renderPass->getName().c_str());

			s_renderPasses.push_back(renderPass);
			renderPass->init(s_rendererAPI);
		}

		void Renderer::Submit(const std::shared_ptr<Renderable>& renderable)
		{
			CHECK_INIT

			s_renderables.push_back(renderable);
		}

		void Renderer::Submit(const std::shared_ptr<CameraData>& cameraData)
		{
			CHECK_INIT

			s_cameraData = cameraData;
		}

		void Renderer::Submit(const std::shared_ptr<LightingData>& lightingData)
		{
			CHECK_INIT

			s_lightingData = lightingData;
		}

		void Renderer::Render()
		{
			CHECK_INIT

			if (s_renderPasses.size() == 0)
			{
				LOG_WARN("No render passes has been submitted to the renderer!");
			}

			if (s_renderables.size() == 0)
			{
				LOG_WARN("No renderables has been submitted to the renderer!");
			}

			if (s_cameraData == nullptr)
			{
				LOG_WARN("No camera data available while trying to render!");
			}

			for (const auto& pass : s_renderPasses)
			{
				pass->execute(s_renderables, s_cameraData, s_lightingData);
			}

			s_renderables.clear();
		}
	}
}
