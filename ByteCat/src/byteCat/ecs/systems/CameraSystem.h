#pragma once
#include "byteCat/app/Application.h"
#include "byteCat/ecs/System.h"
#include "byteCat/ecs/components/Camera.h"
#include "byteCat/ecs/components/Transform.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/utils/Math.h"

namespace BC
{
	class CameraSystem : public System
	{
	public:
		void onUpdate() override
		{
			auto& window = Application::GetInstance().getWindow();
			float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);
			
			for (auto& entity : m_entities)
			{				
				auto transform = m_coordinator->getComponent<Transform>(entity);
				auto camera = m_coordinator->getComponent<Camera>(entity);
				
				Renderer::SetSceneData({
						Math::CreateViewMatrix(transform->position, transform->rotation),
						camera->getProjectionMatrix(aspect) });
			}
		}

		Entity getMainCamera()
		{
			for (auto& entity : m_entities)
			{
				return entity;
			}

			return -1;
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
