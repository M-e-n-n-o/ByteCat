#pragma once

#include "byteCat/render/vertex-object/VertexArray.h"
#include "glm/vec4.hpp"

namespace BC
{
	namespace RenderAPI
	{
		void Init();

		void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

		void ClearColor(const glm::vec4& color);

		void Clear();

		void Draw(const std::shared_ptr<VertexArray>& vao, unsigned int indexCount = 0);
	};
}
