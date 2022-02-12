#pragma once
#include <memory>
#include "byteCat/ecs/Entity.h"
#include "byteCat/graphics/components/Shader.h"

namespace BC
{
	struct Material : Component
	{
		std::shared_ptr<Shader> shader;

		Material() = default;
		Material(const std::shared_ptr<Shader>& shader)
			: shader(shader)
		{
		}

		TYPE_NAME("Material")
	};
}
