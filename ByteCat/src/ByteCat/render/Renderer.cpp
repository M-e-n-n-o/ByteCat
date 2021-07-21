#include "bcpch.h"
#include "byteCat/render/Renderer.h"
#include "byteCat/render/RenderAPI.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	void Renderer::Init()
	{
		gameObjects.reserve(ALLOCATE_PER_RESIZE);
		
		sceneData = std::make_unique<SceneData>();
		
		RenderAPI::Init();
	}

	void Renderer::Shutdown()
	{
		gameObjects.clear();
		gameObjects.shrink_to_fit();
	}

	void Renderer::OnWindowResize(unsigned width, unsigned height)
	{
		RenderAPI::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
	{
		sceneData->viewMatrix = viewMatrix;
		sceneData->projectionMatrix = projectionMatrix;
		
		drawCalls = 0;
		RenderAPI::Clear();
		RenderAPI::ClearColor(CLEAR_COLOR);
	}

	void Renderer::EndScene()
	{
		// TODO
		// Sorteer de entities
		// Render de entities efficient

		for (std::shared_ptr<GameObject>& gameObject : gameObjects)
		{
			auto comp = gameObject->getComponentOfType<RenderComponent>();
			if (comp == nullptr)
			{
				continue;
			}
			
			VertexArray* vao = comp->prepareRender(sceneData->viewMatrix, sceneData->projectionMatrix);
			if (vao != nullptr)
			{
				Render(vao);
				comp->finishRender();
			}
		}

		gameObjects.clear();
		gameObjects.shrink_to_fit();
		gameObjects.reserve(ALLOCATE_PER_RESIZE);
	}

	void Renderer::Submit(std::shared_ptr<GameObject>& gameObject)
	{
		if (gameObjects.size() >= gameObjects.capacity())
		{
			gameObjects.reserve(gameObjects.capacity() + ALLOCATE_PER_RESIZE);
		}
		
		gameObjects.push_back(gameObject);
	}

	void Renderer::Render(const VertexArray* vao)
	{
		++drawCalls;
		RenderAPI::Draw(vao);
	}
}
