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
		renderedEntities = 0;
		RenderAPI::Clear();
		RenderAPI::ClearColor(CLEAR_COLOR);
	}

	void Renderer::EndScene()
	{		
		// Sort the entities by their shader and vao
		std::map<VertexArray*, std::map<std::shared_ptr<Shader>, std::vector<RenderComponent*>>> sortedEntities;
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
			VertexArray* vao = mesh->getVao().get();

			// Insert an entity which can be rendered into the sorted entities map
			auto vertexIterator = sortedEntities.find(vao);
			if (vertexIterator == sortedEntities.end())
			{
				// Not existing vao, not existing shader
				std::vector<RenderComponent*> renderComps;
				renderComps.push_back(renderComp);
				std::map<std::shared_ptr<Shader>, std::vector<RenderComponent*>> shaderMap;
				shaderMap.insert({ shader, renderComps });
				sortedEntities.insert({ vao,  shaderMap});
				
			} else
			{
				auto shaderIterator = vertexIterator->second.find(shader);
				if (shaderIterator == vertexIterator->second.end())
				{
					// Existing vao, not existing shader
					std::vector<RenderComponent*> renderComps;
					renderComps.push_back(renderComp);
					vertexIterator->second.insert({ shader, renderComps });
				} else
				{
					// Existing vao, existing shader
					shaderIterator->second.push_back(renderComp);
				}
			}		
		}

		// Render the sorted entities
		for (const auto& vertexPair : sortedEntities)
		{
			// Bind the vao
			vertexPair.first->bind();
			
			for (const auto& shaderPair : vertexPair.second)
			{
				// Bind the shader
				shaderPair.first->bind();
				
				// Load the standard projection- and viewMatrix into the shader
				shaderPair.first->loadMatrix4("projectionMatrix", sceneData->projectionMatrix);
				shaderPair.first->loadMatrix4("viewMatrix", sceneData->viewMatrix);
				
				for (const auto& renderComp : shaderPair.second)
				{
					// Render the entity
					renderComp->prepareRender(sceneData->viewMatrix, sceneData->projectionMatrix);
					Render(vertexPair.first);
					renderComp->finishRender();

					++renderedEntities;
				}

				// Unbind the shader
				shaderPair.first->unbind();
			}

			// Unbind the vao
			vertexPair.first->unbind();
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
