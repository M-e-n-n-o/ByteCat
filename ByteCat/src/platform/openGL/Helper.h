#pragma once
#include "byteCat/graphics/components/Texture.h"

#if defined(BC_PLATFORM_PC)
	#include <glad/glad.h>
#elif defined(BC_PLATFORM_MOBILE)
	#include <glfm.h>
#endif

namespace BC
{
	namespace Platform
	{
		static int TextureFormatToOpenGLInternalFormat(const Graphics::TextureFormat& format)
		{
			switch (format)
			{
			case Graphics::TextureFormat::DEPTH:			return GL_DEPTH_COMPONENT;
			case Graphics::TextureFormat::DEPTH_STENCIL:	return GL_DEPTH_STENCIL;
			case Graphics::TextureFormat::R:				return GL_RED;
			case Graphics::TextureFormat::RG:				return GL_RG;
			case Graphics::TextureFormat::RGB16F:			return GL_RGB16F;
			case Graphics::TextureFormat::RGBA8:			return GL_RGBA8;
			case Graphics::TextureFormat::RGBA16F:		return GL_RGBA16F;
			}

			return -1;
		}

		static int TextureFormatToOpenGLFormat(const Graphics::TextureFormat& format)
		{
			switch (format)
			{
			case Graphics::TextureFormat::DEPTH:			return GL_DEPTH_COMPONENT;
			case Graphics::TextureFormat::DEPTH_STENCIL:	return GL_DEPTH_STENCIL;
			case Graphics::TextureFormat::R:				return GL_RED;
			case Graphics::TextureFormat::RG:				return GL_RG;
			case Graphics::TextureFormat::RGB16F:			return GL_RGB;
			case Graphics::TextureFormat::RGBA8:			return GL_RGBA;
			case Graphics::TextureFormat::RGBA16F:		return GL_RGBA;
			}

			return -1;
		}
	}
}
