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
		private:
			inline static glm::vec3 m_cameraPos;

		public:
			static void onRenderRenderable(const Graphics::Renderable& renderable)
			{
				renderable.shader->loadVector3("_cameraPos", m_cameraPos);

				static float time = App::Time::GetDeltaTime();
				time += App::Time::GetDeltaTime();
				renderable.shader->loadFloat("_time", time);
				if (time > 10000) { time = 0; }
			}

			void onUpdate() override
			{
				Entity camera = m_coordinator->getSystem<CameraSystem>()->getMainCamera();
				if (camera != -1)
				{
					m_cameraPos = m_coordinator->getComponent<Transform>(camera)->position;
				}

				for (auto& entity : m_entities)
				{
					auto transform = m_coordinator->getComponent<Transform>(entity);
					auto mesh = m_coordinator->getComponent<Mesh>(entity);
					auto material = m_coordinator->getComponent<Material>(entity);

					glm::mat4 modelMatrix = Utils::Math::CreateModelMatrix(transform->position, transform->rotation, transform->scale);
					Graphics::Renderer::Submit({ material->cullingMode, mesh->vao, material->shader, material->textures, modelMatrix, onRenderRenderable });
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
