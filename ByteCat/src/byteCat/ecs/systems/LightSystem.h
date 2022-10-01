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
				for (auto& entity : m_entities)
				{
					auto light = m_coordinator->getComponent<Light>(entity);

					
				}
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
