#include "bcpch.h"
#include <stb_image.h>
#include <glad/glad.h>
#include "byteCat/utils/Macro.h"
#include "platform/openGL/OpenGLTexture2D.h"
#include "platform/openGL/Helper"

namespace BC
{
	namespace Platform
	{
		OpenGLTexture2D::OpenGLTexture2D(unsigned width, unsigned height, const TextureFormat& format)
		{
			m_width = width;
			m_height = height;
			m_format = format;

			if (format == TextureFormat::AUTO)
			{
				LOG_ERROR("Cannot auto format an empty texture!");
				return;
			}
			
			glGenTextures(1, &m_id);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_id);
			
			glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToOpenGLFormat(format), width, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath, const TextureFormat& format, float mipmapLOD)
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
				m_format = TextureFormat::RGBA;
				internalFormat = TextureFormatToOpenGLFormat(TextureFormat::RGBA);
				dataFormat = GL_RGBA;
			}
			else if (m_channels == 3)
			{
				m_format = TextureFormat::RGB;
				internalFormat = TextureFormatToOpenGLFormat(TextureFormat::RGB);
				dataFormat = GL_RGB;
			} else
			{
				LOG_ERROR("Image format not supported for texture2D: {0}", finalPath);
				stbi_image_free(imgData);
				return;
			}

			if (format != TextureFormat::AUTO)
			{
				m_format = format;
				internalFormat = TextureFormatToOpenGLFormat(format);
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
