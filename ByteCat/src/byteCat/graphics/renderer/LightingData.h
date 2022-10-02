#pragma once
#include <memory>
#include <vector>
#include "byteCat/ecs/components/Light.h"

namespace BC
{
	namespace Graphics
	{
		struct LightingData
		{
			Ecs::DirectionalLight* sun = nullptr;

			std::vector<Ecs::Light*> lights;
		};
	}
}
