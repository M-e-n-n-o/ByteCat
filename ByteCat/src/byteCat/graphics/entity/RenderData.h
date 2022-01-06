#pragma once
#include "byteCat/graphics/entity/VertexArray.h"
#include "byteCat/graphics/entity/Shader.h"

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
