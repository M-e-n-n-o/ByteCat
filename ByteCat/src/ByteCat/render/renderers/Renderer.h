#pragma once

#include <glm/glm.hpp>

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
	};
}
