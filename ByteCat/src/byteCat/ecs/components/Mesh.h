#pragma once
#include <memory>
#include "byteCat/ecs/Entity.h"
#include "byteCat/graphics/components/VertexArray.h"

namespace BC
{
	namespace Ecs
	{
		struct Mesh : Component
		{
			std::shared_ptr<Graphics::VertexArray> vao;

			Mesh() = default;
			Mesh(const std::shared_ptr<Graphics::VertexArray>& vao)
				: vao(vao) {}

			virtual ~Mesh() = default;

			TYPE_NAME("Mesh")
		};
	}
}
