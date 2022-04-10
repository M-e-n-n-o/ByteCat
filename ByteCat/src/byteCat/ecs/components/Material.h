#pragma once
#include <memory>
#include "byteCat/ecs/Entity.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"
#include "byteCat/graphics/renderer/RenderModes.h"

namespace BC
{
	namespace Ecs
	{
		struct Material : Component
		{
			Graphics::CullingMode cullingMode;
			// RenderLayer renderLayer;

			std::shared_ptr<Graphics::Shader> shader;
			std::vector<std::shared_ptr<Graphics::Texture>> textures;

			Material() = default;
			Material(const Graphics::CullingMode& cullingMode, const std::shared_ptr<Graphics::Shader>& shader)
				: cullingMode(cullingMode), shader(shader)
			{
			}

			Material(const Graphics::CullingMode& cullingMode, const std::shared_ptr<Graphics::Shader>& shader, std::initializer_list<std::shared_ptr<Graphics::Texture>> textureSlots)
				: cullingMode(cullingMode), shader(shader), textures(textureSlots)
			{
			}

			TYPE_NAME("Material")
		};
	}
}
