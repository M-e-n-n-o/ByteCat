#ifdef BC_PLATFORM_PC
#include "bcpch.h"
#include <glad/glad.h>
#include "platform/openGL/OpenGLTexture3D.h"
#include "platform/openGL/Helper.h"

namespace BC
{
	namespace Platform
	{
		OpenGLTexture3D::OpenGLTexture3D(unsigned width, unsigned height, unsigned depth, const Graphics::TextureFormat& format)
		{
			m_width = width;
			m_height = height;
			m_format = format;
			m_channels = 3;

			if (format == Graphics::TextureFormat::AUTO)
			{
				LOG_ERROR("Cannot auto format an empty texture!");
				return;
			}

			glGenTextures(1, &m_id);
			glEnable(GL_TEXTURE_3D);
			glBindTexture(GL_TEXTURE_3D, m_id);

			glTexImage3D(GL_TEXTURE_3D, 0, TextureFormatToOpenGLInternalFormat(format), width, height, depth, 0, TextureFormatToOpenGLFormat(format), GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		OpenGLTexture3D::~OpenGLTexture3D()
		{
			glDeleteTextures(1, &m_id);
		}

		void OpenGLTexture3D::bind(unsigned textureUnit) const
		{
			glBindTextureUnit(textureUnit, m_id);
		}
	}
}
#endif