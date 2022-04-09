#include "bcpch.h"
#include "byteCat/graphics/renderer/Renderer.h"

namespace BC
{
	#define CHECK_INIT if(!s_hasRenderer) return;

	void Renderer::SetAPI(const GraphicsAPI& api)
	{
		if (s_graphicsAPI == GraphicsAPI::None)
		{
			s_graphicsAPI = api;
			s_rendererAPI = RendererAPI::Create(s_graphicsAPI);
		}
	}
	
	void Renderer::Init(BaseRenderer* renderer)
	{		
		if (renderer == nullptr)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(s_graphicsAPI))
		{
			LOG_WARN("{0} does not support the selected graphics API!", renderer->getName());
			delete renderer;
			return;
		}

		if (!s_hasRenderer)
		{
			s_hasRenderer = true;

			// const char* name = typeid(renderer).name();
			// LOG_INFO("Setting renderer to: {0}", name);
			
			s_activeRenderer = renderer;
			s_activeRenderer->init(s_rendererAPI);
		}
	}

	void Renderer::SetRenderer(BaseRenderer* renderer)
	{
		if (renderer == nullptr || !s_hasRenderer)
		{
			delete renderer;
			return;
		}

		if (!renderer->supports(s_graphicsAPI))
		{
			LOG_WARN("{0} does not support the selected graphics API!", renderer->getName());
			delete renderer;
			return;
		}

		// const char* name = typeid(renderer).name();
		// LOG_INFO("Setting renderer to: {0}", name);

		delete s_activeRenderer;
		s_activeRenderer = renderer;
		s_activeRenderer->init(s_rendererAPI);
	}

	void Renderer::Shutdown()
	{
		delete s_rendererAPI;
		delete s_activeRenderer;
	}

	void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
	{
		CHECK_INIT

		s_rendererAPI->setViewport(x, y, width, height);
	}

	void Renderer::Clear(const glm::vec3& color)
	{
	}

	void Renderer::SetColor(const glm::vec4& color)
	{
	}

	void Renderer::DrawRectangle(const glm::vec3& position, const glm::vec3& scale)
	{
	}

	void Renderer::DrawImage(const glm::vec3& position, const glm::vec3& scale, std::shared_ptr<Texture2D> texture)
	{
	}

	void Renderer::Submit(const Renderable& renderable)
	{
		CHECK_INIT
		
		s_activeRenderer->submit(renderable);
	}

	void Renderer::SetSceneData(const SceneData& sceneData)
	{
		CHECK_INIT

		s_activeRenderer->setSceneData(sceneData);
	}

	void Renderer::RenderSubmissions()
	{
		CHECK_INIT

		s_activeRenderer->renderSubmissions();
	}
}
