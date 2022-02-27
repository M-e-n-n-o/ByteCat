#pragma once
#include <glad/glad.h>
#include <fstream>
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
			case TextureFormat::DEPTH:			return GL_DEPTH_COMPONENT;
			case TextureFormat::DEPTH_STENCIL:	return GL_DEPTH_STENCIL;
			case TextureFormat::R:				return GL_RED;
			case TextureFormat::RG:				return GL_RG;
			case TextureFormat::RGB16F:			return GL_RGB16F;
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
			case TextureFormat::RGBA16F:		return GL_RGBA;
			}

			return -1;
		}

		static std::string ReadFileIntoString(const std::string& path) {
			std::ifstream input_file(path);

			if (!input_file.is_open()) {
				LOG_ERROR("Could not open the shader file: {0}", path);
				return "";
			}

			std::string text = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

			input_file.close();

			return text;
		}
	}
}
