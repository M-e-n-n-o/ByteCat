#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "bcpch.h"
#include <stb_image.h>
#include "platform/openGL/OpenGLTexture2D.h"
#include "platform/openGL/Helper.h"
#include "byteCat/utils/FileIO.h"

#if defined(BC_PLATFORM_PC)
	#include <glad/glad.h>
#elif defined(BC_PLATFORM_MOBILE)
	#include <glfm.h>
#endif

namespace BC
{
	namespace Platform
	{
		OpenGLTexture2D::OpenGLTexture2D(unsigned width, unsigned height, const Graphics::TextureFormat& format)
		{
			m_width = width;
			m_height = height;
			m_format = format;

			switch (format)
			{
			case Graphics::TextureFormat::R8: m_channels = 1; break;
			case Graphics::TextureFormat::RG8: m_channels = 2; break;
			case Graphics::TextureFormat::RGB16F: m_channels = 3; break;
			case Graphics::TextureFormat::RGBA16F: m_channels = 4; break;
			default: m_channels = 3;
			}

			if (format == Graphics::TextureFormat::AUTO)
			{
				LOG_ERROR("Cannot auto format an empty texture!");
				return;
			}
			
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			
			glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToOpenGLInternalFormat(format), m_width, m_height, 0, TextureFormatToOpenGLFormat(format), GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath, const Graphics::TextureFormat& format, float mipmapLOD)
		{
			LOG_INFO("Loading texture2D: %s", filePath.c_str());

			unsigned char* imgData = nullptr;
			stbi_set_flip_vertically_on_load(1);

		#if defined(BC_PLATFORM_PC)
			imgData = stbi_load(Utils::FileIO::GetRelativePath(filePath).c_str(), &m_width, &m_height, &m_channels, 0);

		#elif defined(BC_PLATFORM_ANDROID)
			std::vector<unsigned char> assetContent;

			bool success = Utils::FileIO::GetDataFromAssets(filePath, assetContent);
			if (!success)
			{
				LOG_ERROR("Failed to load texture from Assets: %s", filePath.c_str());
				return;
			}

			imgData = stbi_load_from_memory(assetContent.data(), assetContent.size(), &m_width, &m_height, &m_channels, 0);
		#endif

			if (!imgData)
			{
				LOG_ERROR("Failed to load texture2D: %s", filePath.c_str());
				stbi_image_free(imgData);
				return;
			}

			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);

			if (m_channels == 4)
			{
				m_format = Graphics::TextureFormat::RGBA16F;
			}
			else if (m_channels == 3)
			{
				m_format = Graphics::TextureFormat::RGB16F;
			} else
			{
				LOG_ERROR("Image format not supported for texture2D: %s", filePath.c_str());
				stbi_image_free(imgData);
				return;
			}

			int internalFormat = TextureFormatToOpenGLInternalFormat(m_format);
			int dataFormat = TextureFormatToOpenGLFormat(m_format);

			if (format != Graphics::TextureFormat::AUTO)
			{
				m_format = format;
				internalFormat = TextureFormatToOpenGLInternalFormat(format);
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, imgData);

			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			#if defined(BC_PLATFORM_PC)
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, mipmapLOD);
			#elif defined(BC_PLATFORM_MOBILE)
				if (mipmapLOD != 0) LOG_WARN("Changing the LOD does not have any effect on OpenGLES");
			#endif

			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// glBindTexture(GL_TEXTURE_2D, 0);

			// m_textureData = imgData;
			stbi_image_free(imgData);
		}

		OpenGLTexture2D::~OpenGLTexture2D()
		{
			glDeleteTextures(1, &m_id);

			// if (m_textureData != nullptr)
			// {
			// 	stbi_image_free(m_textureData);
			// }
		}

		void OpenGLTexture2D::bind(unsigned textureUnit) const
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, m_id);
		}

		void OpenGLTexture2D::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		// unsigned char OpenGLTexture2D::getValue(unsigned channel, unsigned x, unsigned y) const
		// {
		// 	if (channel + 1 > m_channels)
		// 	{
		// 		LOG_ERROR("Channel {0} does not exist in the image, total channels is {1}", channel, m_channels);
		// 		return -1;
		// 	}
		//
		// 	if (m_textureData == nullptr)
		// 	{
		// 		LOG_ERROR("Could not get the texture data");
		// 		return -1;
		// 	}
		//
		// 	unsigned char* pixelOffset = m_textureData + (x + m_height * y) * m_channels;
		//
		// 	if (&pixelOffset[channel] == nullptr)
		// 	{
		// 		LOG_ERROR("Given x, y ({0}, {1}) coordinates were out of range when reading from the texture data", x, y);
		// 		return -1;
		// 	}
		//
		// 	return pixelOffset[channel];
		// }
	}
}
#endif