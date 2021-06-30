#pragma once

#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/Shader.h"

namespace BC
{
	class StandardShader : public Shader
	{
	private:
	
	public:
		StandardShader(Texture2D& texture);

		void setMainTexture(Texture2D& texture) { bindTexture(texture); }
	};
}
