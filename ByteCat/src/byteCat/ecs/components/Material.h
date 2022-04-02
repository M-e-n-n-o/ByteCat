#pragma once
#include <memory>
#include "byteCat/ecs/Entity.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"
#include "byteCat/graphics/renderer/RenderModes.h"

namespace BC
{
	struct Material : Component
	{
		CullingMode cullingMode;
		// RenderLayer renderLayer;
		
		std::shared_ptr<Shader> shader;
		std::vector<std::shared_ptr<Texture>> textures;

		Material() = default;
		Material(const CullingMode& cullingMode, const std::shared_ptr<Shader>& shader)
			: cullingMode(cullingMode), shader(shader)
		{
		}

		Material(const CullingMode& cullingMode, const std::shared_ptr<Shader>& shader, std::initializer_list<std::shared_ptr<Texture>> textureSlots)
			: cullingMode(cullingMode), shader(shader), textures(textureSlots)
		{
		}

		TYPE_NAME("Material")
	};
}
