#pragma once
#include "byteCat/render/shaders/ShaderProgram.h"

namespace BC
{
	class StandardShader : public ShaderProgram
	{
	private:
	
	public:
		StandardShader();
	
	protected:
		void getAllUniformLocations() override;
		void bindAttributes() override;
	};
}
