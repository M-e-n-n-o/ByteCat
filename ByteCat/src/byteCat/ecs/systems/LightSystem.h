#pragma once
#include "byteCat/ecs/System.h"
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/components/Light.h"

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

					if (auto directional = dynamic_cast<DirectionalLight*>(light); directional != nullptr)
					{
						lightingData->sun = directional;
						continue;
					}

					lightingData->lights.push_back(light);
				}

				Graphics::Renderer::Submit(lightingData);
			}

			static Dependencies GetDependencies(EcsCoordinator* coordinator)
			{
				Dependencies signature;
				signature.set(coordinator->getComponentType<Light>());
				return signature;
			}
		};
	}
}
