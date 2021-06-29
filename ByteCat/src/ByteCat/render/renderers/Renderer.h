#pragma once

#include <glm/glm.hpp>
#include "byteCat/render/models/Mesh.h"
#include "byteCat/render/shaders/Shader.h"

namespace BC
{
	class Renderer
	{
	protected:
		glm::vec3 CLEAR_COLOR = { 0.3f, 0.4f, 0.6f };
		
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		void prepare() const;

		void renderVAO(VAO& vao, Shader& shader);
	};
}
