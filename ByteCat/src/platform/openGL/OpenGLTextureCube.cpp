#include "bcpch.h"
#include <stb_image.h>
#include <glad/glad.h>
#include "platform/openGL/OpenGLTextureCube.h"

namespace BC
{
	namespace Platform
	{
		OpenGLTextureCube::OpenGLTextureCube(const std::vector<std::string>& textures, const TextureFormat& format)
		{
			m_format = format;

			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

			// Do the things
			
		}

		OpenGLTextureCube::~OpenGLTextureCube()
		{
			glDeleteTextures(1, &m_id);
		}

		void OpenGLTextureCube::bind(unsigned textureUnit) const
		{
			glBindTextureUnit(textureUnit, m_id);
		}
	}
}
