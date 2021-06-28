#pragma once

#include "byteCat/render/renderers/Renderer.h"
#include "byteCat/render/models/Model.h"

namespace BC
{
	class MeshRenderer : public Renderer
	{
	public:
		MeshRenderer() = default;
		~MeshRenderer() = default;
		
		void render(TexturedModel& texturedModel);
	};
}