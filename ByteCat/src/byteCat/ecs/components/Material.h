#pragma once
#include <memory>
#include "byteCat/ecs/Entity.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"

namespace BC
{	
	struct Material : Component
	{
		std::shared_ptr<Shader> shader;
		std::vector<std::shared_ptr<Texture>> textures;

		Material() = default;
		Material(const std::shared_ptr<Shader>& shader)
			: shader(shader)
		{
		}

		Material(const std::shared_ptr<Shader>& shader, std::initializer_list<std::pair<const char*, std::shared_ptr<Texture>>> textureSlots)
			: shader(shader)
		{
			shader->bind();

			int i = 0;
			for (auto& textureSlot : textureSlots)
			{
				shader->loadInt(textureSlot.first, i++);
				textures.push_back(textureSlot.second);
			}
		}

		TYPE_NAME("Material")
	};
}
