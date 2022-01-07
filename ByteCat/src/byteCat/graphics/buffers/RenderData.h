#pragma once
#include "byteCat/graphics/buffers/VertexArray.h"
#include "byteCat/graphics/buffers/Shader.h"

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
