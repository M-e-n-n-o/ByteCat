#include "bcpch.h"
#include "byteCat/render/Renderer.h"

#include "byteCat/entity-system/Material.h"
#include "byteCat/entity-system/Mesh.h"
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

	void Renderer::SetRenderMode(RenderMode const& mode)
	{
		RenderAPI::SetRenderMode(mode);
	}

	void Renderer::SetCullingMode(RenderCulling const& mode)
	{
		RenderAPI::SetRenderCulling(mode);
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
		// Sort the entities by their shader
		std::map<std::shared_ptr<Shader>, std::map<VertexArray*, RenderComponent*>> sortedEntities;
		for (std::shared_ptr<GameObject>& gameObject : gameObjects)
		{
			auto renderComp = gameObject->getComponent<RenderComponent>();
			if (renderComp == nullptr)
			{
				continue;
			}

			Material* mat = gameObject->getComponent<Material>();
			if (mat == nullptr)
			{
				LOG_ERROR("{0} cannot be rendered because it does not have a material", gameObject->name);
				continue;
			}

			auto mesh = gameObject->getComponent<Mesh>();
			if (mesh == nullptr)
			{
				LOG_ERROR("{0} cannot be rendered because it does not have a mesh", gameObject->name);
				continue;
			}

			std::shared_ptr<Shader> shader = mat->getShader();

			// Insert an entity which can be rendered into the sorted entities map
			auto it = sortedEntities.find(shader);
			if (it == sortedEntities.end())
			{
				std::map<VertexArray*, RenderComponent*> vaos;
				vaos.insert(std::pair<VertexArray*, RenderComponent*>(mesh->getVao().get(), renderComp));
				sortedEntities.insert(std::pair<std::shared_ptr<Shader>, std::map<VertexArray*, RenderComponent*>>(shader, vaos));
			} else
			{
				it->second.insert(std::pair<VertexArray*, RenderComponent*>(mesh->getVao().get(), renderComp));
			}		
		}

		// Render the sorted entities
		for (const auto& shaderPair : sortedEntities)
		{
			shaderPair.first->bind();

			// Load the standard projection- and viewMatrix into the shader
			shaderPair.first->loadMatrix4("projectionMatrix", sceneData->projectionMatrix);
			shaderPair.first->loadMatrix4("viewMatrix", sceneData->viewMatrix);
			
			for (const auto& renderPair : shaderPair.second)
			{
				// Render the entity
				renderPair.second->prepareRender(sceneData->viewMatrix, sceneData->projectionMatrix);
				renderPair.first->bind();
				Render(renderPair.first);
				renderPair.first->unbind();
				renderPair.second->finishRender();
			}

			shaderPair.first->unbind();
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
