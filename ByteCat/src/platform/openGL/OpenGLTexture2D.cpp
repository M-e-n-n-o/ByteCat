#include "bcpch.h"
#include <stb_image.h>
#include <glad/glad.h>
#include "byteCat/utils/Macro.h"
#include "platform/openGL/OpenGLTexture2D.h"

namespace BC
{
	namespace Platform
	{

		
		OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath, float mipmapLOD)
		{
			std::string finalPath = filePath;
			finalPath.insert(0, BC_ASSETS_FOLDER);

			LOG_INFO("Loading texture2D: {0}", finalPath);

			stbi_set_flip_vertically_on_load(1);
			unsigned char* imgData = stbi_load(finalPath.c_str(), &m_width, &m_height, &m_channels, 0);
			if (!imgData)
			{
				LOG_ERROR("Failed to load texture2D: {0}", finalPath);
				stbi_image_free(imgData);
				return;
			}

			glGenTextures(1, &m_id);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_id);

			int internalFormat = 0;
			int dataFormat = 0;
			if (m_channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (m_channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			} else
			{
				LOG_ERROR("Image format not supported for texture2D: {0}", finalPath);
				stbi_image_free(imgData);
				return;
			}
			
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, imgData);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, mipmapLOD);

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(imgData);
		}

		OpenGLTexture2D::~OpenGLTexture2D()
		{
			glDeleteTextures(1, &m_id);
		}

		void OpenGLTexture2D::bind(unsigned textureUnit) const
		{
			glBindTextureUnit(textureUnit, m_id);
		}
	}
}
