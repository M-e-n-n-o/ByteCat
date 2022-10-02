#pragma once
#include "byteCat/app/Application.h"
#include "byteCat/ecs/System.h"
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/components/Camera.h"
#include "byteCat/ecs/components/Transform.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	namespace Ecs
	{
		class CameraSystem : public System
		{
		private:
			Entity m_mainCamera = -1;

		public:
			void onUpdate() override
			{
				if (m_mainCamera == -1)
				{
					LOG_WARN("No camera has been found!");
					return;
				}

				auto& window = App::Application::GetInstance().getWindow();
				float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);

				auto transform = m_coordinator->getComponent<Transform>(m_mainCamera);
				auto camera = m_coordinator->getComponent<Camera>(m_mainCamera);

				auto camData = std::make_shared<Graphics::CameraData>(transform->position, Utils::Math::CreateViewMatrix(transform->position, transform->rotation), camera->getProjectionMatrix(aspect));
				Graphics::Renderer::Submit(camData);
			}

			void onEntitiesChanged() override
			{
				bool found = false;

				for (auto& m_entity : m_entities)
				{
					if (m_entity == m_mainCamera)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					m_mainCamera = -1;
					m_mainCamera = getMainCamera();
				}
			}

			void setMainCamera(Entity entity)
			{
				for (auto& m_entity : m_entities)
				{
					if (m_entity == entity)
					{
						m_mainCamera = entity;
						return;
					}
				}

				LOG_WARN("Given entity cannot be set as the main camera!");
			}

			Entity getMainCamera()
			{
				if (m_entities.empty())
				{
					return -1;
				}

				if (m_mainCamera == -1)
				{
					m_mainCamera = *m_entities.begin();
				}

				return m_mainCamera;
			}

			static Dependencies GetDependencies(EcsCoordinator* coordinator)
			{
				Dependencies signature;
				signature.set(coordinator->getComponentType<Transform>());
				signature.set(coordinator->getComponentType<Camera>());
				return signature;
			}
		};
	}
}
