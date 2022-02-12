#pragma once
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/components/Shader.h"

namespace BC
{
	struct Renderable
	{
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<Shader> shader;
		glm::mat4 modelMatrix;
	};


	struct SceneData
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}