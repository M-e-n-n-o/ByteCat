#pragma once
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/components/Shader.h"

namespace BC
{
	struct Renderable
	{
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<Shader> shader;
	};


	struct SceneData
	{

	};
}