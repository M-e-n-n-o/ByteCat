#pragma once

#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/Shader.h"

namespace BC
{
	class StandardShader : public Shader
	{
	private:
		std::shared_ptr<Texture2D> mainTexture;
	
	public:
		StandardShader(Texture2D& texture);

		void setMainTexture(Texture2D& texture) { mainTexture = std::make_shared<Texture2D>(texture); }
	};
}
