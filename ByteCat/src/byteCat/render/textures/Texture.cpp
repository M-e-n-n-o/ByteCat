#include "bcpch.h"
#include <glad/glad.h>
#include <stb_image.h>
#include "byteCat/render/textures/Texture.h"

namespace BC
{
	Texture2D::Texture2D(std::string& filePath, float mipmapLOD)
	{
		LOG_INFO("Loading texture: {0}", filePath);
		
		int width, height, bpp;
		unsigned char* imgData = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);
		LOG_ASSERT(imgData, "Failed to load the texture: {0}", filePath);

		this->width = width;
		this->height = height;
		this->bpp = bpp;
		
		glGenTextures(1, &textureID);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

		// Set mipmapping
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, mipmapLOD);
		
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
