#pragma once
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Graphics
	{
		/**
		 * @brief
		 * This renderer is used to draw simple 2D geometry without much hassle.
		 * The Renderer still has to be initialized before you will be able to use this renderer!
		 */
		class Renderer2D
		{		
		public:
			static void Clear(const glm::vec4& color);
			static void SetColor(const glm::vec4& color);
			static void DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& scale);
			static void DrawImage(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture);
		};
	}
}
