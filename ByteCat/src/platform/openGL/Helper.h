#pragma once
#include <glad/glad.h>
#include "byteCat/Log.h"
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{
		static int TextureFormatToOpenGLInternalFormat(const TextureFormat& format)
		{
			switch (format)
			{
			case TextureFormat::DEPTH:			return GL_DEPTH_COMPONENT32;
			case TextureFormat::DEPTH_STENCIL:	return GL_DEPTH24_STENCIL8;
			case TextureFormat::R:				return GL_RED;
			case TextureFormat::RG:				return GL_RG;
			case TextureFormat::RGB16F:			return GL_RGB16F;
			case TextureFormat::RGBA8:			return GL_RGBA8;
			case TextureFormat::RGBA16F:		return GL_RGBA16F;
			}

			return -1;
		}

		static int TextureFormatToOpenGLFormat(const TextureFormat& format)
		{
			switch (format)
			{
			case TextureFormat::DEPTH:			return GL_DEPTH_COMPONENT;
			case TextureFormat::DEPTH_STENCIL:	return GL_DEPTH_STENCIL;
			case TextureFormat::R:				return GL_RED;
			case TextureFormat::RG:				return GL_RG;
			case TextureFormat::RGB16F:			return GL_RGB;
			case TextureFormat::RGBA8:			return GL_RGBA;
			case TextureFormat::RGBA16F:		return GL_RGBA;
			}

			return -1;
		}
	}
}
