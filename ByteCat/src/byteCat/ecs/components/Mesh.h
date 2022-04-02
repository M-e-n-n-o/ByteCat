#pragma once
#include <memory>
#include "byteCat/ecs/Entity.h"
#include "byteCat/graphics/components/VertexArray.h"

namespace BC
{
	struct Mesh : Component
	{
		std::shared_ptr<VertexArray> vao;

		Mesh() = default;
		Mesh(const std::shared_ptr<VertexArray>& vao)
			: vao(vao) {}
		
		virtual ~Mesh() = default;
		
		TYPE_NAME("Mesh")
	};
}
