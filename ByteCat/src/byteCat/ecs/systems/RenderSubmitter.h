#pragma once
#include "byteCat/app/Time.h"
#include "byteCat/ecs/SceneManager.h"
#include "byteCat/ecs/System.h"
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/components/Material.h"
#include "byteCat/ecs/components/Mesh.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	namespace Ecs
	{
		class RenderSubmitter : public System
		{
		public:
			void onUpdate() override
			{
				for (auto& entity : m_entities)
				{
					auto transform = m_coordinator->getComponent<Transform>(entity);
					auto mesh = m_coordinator->getComponent<Mesh>(entity);
					auto material = m_coordinator->getComponent<Material>(entity);

					glm::mat4 modelMatrix = Utils::Math::CreateModelMatrix(transform->position, transform->rotation, transform->scale);

					auto renderable = std::make_shared<Graphics::Renderable>(material->cullingMode, mesh->vao, material->shader, modelMatrix);
					Graphics::Renderer::Submit(renderable);
				}
			}

			static Dependencies GetDependencies(EcsCoordinator* coordinator)
			{
				Dependencies signature;
				signature.set(coordinator->getComponentType<Transform>());
				signature.set(coordinator->getComponentType<Mesh>());
				signature.set(coordinator->getComponentType<Material>());
				return signature;
			}
		};
	}
}
