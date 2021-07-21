#pragma once

#include "byteCat/render/vertex-object/VertexArray.h"
#include "glm/vec4.hpp"

namespace BC
{
	namespace RenderAPI
	{
		// Call this function to initialize the renderAPI (OpenGL)
		void Init();

		// Call this function to change the size of the OpenGL window
		void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

		// Call this function to clear the window
		void ClearColor(const glm::vec4& color);

		// Call this function to clear the color and depth buffers
		void Clear();

		// Call this function to render a VertexArray
		void Draw(const VertexArray* vao, unsigned int indexCount = 0);
	};
}
