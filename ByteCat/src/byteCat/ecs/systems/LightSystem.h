#pragma once
#include "byteCat/ecs/System.h"
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/components/Light.h"
#include "byteCat/ecs/components/Transform.h"

namespace BC
{
	namespace Ecs
	{
		class LightSystem : public System
		{
		public:
			void onUpdate() override
			{
				auto lightingData = std::make_shared<Graphics::LightingData>();

				for (auto& entity : m_entities)
				{
					auto light = m_coordinator->getComponent<Light>(entity);
					auto transform = m_coordinator->getComponent<Transform>(entity);

					if (auto directional = dynamic_cast<DirectionalLight*>(light); directional != nullptr)
					{
						lightingData->mainLightSource = directional;
						lightingData->mainLightPosition = transform->position;
						continue;
					}

					//lightingData->lights.push_back(light);
				}

				Graphics::Renderer::Submit(lightingData);
			}

			static Dependencies GetDependencies(EcsCoordinator* coordinator)
			{
				Dependencies signature;
				signature.set(coordinator->getComponentType<Light>());
				signature.set(coordinator->getComponentType<Transform>());
				return signature;
			}
		};
	}
}
