#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/models/Texture.h"
#include "byteCat/render/Loader.h"

namespace BC
{
	Texture2D::Texture2D(std::string filePath)
	{
		filePath.insert(0, "res/");
		int width, height;
		this->textureID = Loader::Load2DTexture(filePath, width, height);
		this->width = width;
		this->height = height;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &textureID);
	}

	void Texture2D::bind(unsigned number) const
	{
		switch (number)
		{
			case 0: glActiveTexture(GL_TEXTURE0); break;
			case 1: glActiveTexture(GL_TEXTURE1); break;
			case 2: glActiveTexture(GL_TEXTURE2); break;
			case 3: glActiveTexture(GL_TEXTURE3); break;
			case 4: glActiveTexture(GL_TEXTURE4); break;
			case 5: glActiveTexture(GL_TEXTURE5); break;
			default: LOG_ERROR("Texture unit {0} cannot be used", number); return;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
	}
}
