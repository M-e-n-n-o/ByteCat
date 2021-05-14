#pragma once
#include "byteCat/render/shaders/ShaderProgram.h"

namespace BC
{
	class StaticShader : public ShaderProgram
	{
	public:
		StaticShader();

	protected:
		void bindAttributes() override;
	};
}
