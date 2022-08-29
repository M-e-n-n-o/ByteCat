#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "bcpch.h"
#include <stb_image.h>
#include "platform/openGL/OpenGLTextureCube.h"

#if defined(BC_PLATFORM_PC)
	#include <glad/glad.h>
#elif defined(BC_PLATFORM_MOBILE)
	#include <glfm.h>
#endif

namespace BC
{
	namespace Platform
	{
		OpenGLTextureCube::OpenGLTextureCube(const std::vector<std::string>& faces, const Graphics::TextureFormat& format)
		{
			m_format = format;

			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

			int width, height;
			for (unsigned int i = 0; i < faces.size(); i++)
			{
				std::string filePath = faces[i];
				filePath.insert(0, BC_ASSETS_FOLDER);

				LOG_INFO("Loading cubemap texture face: %s", filePath.c_str());
				
				unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &m_channels, 0);
				if (data)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
				}
				else
				{
					LOG_ERROR("Failed to load cubemap texture face: %s", filePath.c_str());
					stbi_image_free(data);
					return;
				}
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		OpenGLTextureCube::~OpenGLTextureCube()
		{
			glDeleteTextures(1, &m_id);
		}

		void OpenGLTextureCube::bind(unsigned textureUnit) const
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		}
	}
}
#endif