#pragma once
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& fileName, float mipmapLod);
		~OpenGLTexture2D();

		void bind(unsigned textureUnit) const override;
		void unbind() const override;
		
		unsigned getWidth() const override;
		unsigned getHeight() const override;
		unsigned getBpp() const override;
	};
}
