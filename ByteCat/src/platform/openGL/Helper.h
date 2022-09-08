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
			case Graphics::TextureFormat::DEPTH16:			return GL_DEPTH_COMPONENT16;
			case Graphics::TextureFormat::DEPTH24_STENCIL8:	return GL_DEPTH24_STENCIL8;
			case Graphics::TextureFormat::R8:				return GL_R8;
			case Graphics::TextureFormat::RG8:				return GL_RG8;
			case Graphics::TextureFormat::RGB8:				return GL_RGB8;
			case Graphics::TextureFormat::RGBA8:			return GL_RGBA8;
			}

			return -1;
		}

		static int TextureFormatToOpenGLBaseFormat(const Graphics::TextureFormat& format)
		{
			switch (format)
			{
			case Graphics::TextureFormat::DEPTH16:			return GL_DEPTH_COMPONENT;
			case Graphics::TextureFormat::DEPTH24_STENCIL8:	return GL_DEPTH_STENCIL;
			case Graphics::TextureFormat::R8:				return GL_RED;
			case Graphics::TextureFormat::RG8:				return GL_RG;
			case Graphics::TextureFormat::RGB8:				return GL_RGB;
			case Graphics::TextureFormat::RGBA8:			return GL_RGBA;
			}

			return -1;
		}
	}
}
