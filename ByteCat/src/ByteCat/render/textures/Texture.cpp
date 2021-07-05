#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/render/textures/Texture.h"
#include "byteCat/utils/stb_image.h"

namespace BC
{
	Texture2D::Texture2D(std::string& filePath)
	{
		filePath.insert(0, "res/");

		LOG_INFO("Loading texture: {0}", filePath);
		
		int width, height, bpp;
		unsigned char* imgData = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);
		LOG_ASSERT(imgData, "Failed to load the texture");

		this->width = width;
		this->height = height;
		this->bpp = bpp;
		
		glGenTextures(1, &textureID);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(imgData);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &textureID);
	}

	void Texture2D::bind(unsigned textureUnit) const
	{
		glBindTextureUnit(textureUnit, textureID);
	}
}
