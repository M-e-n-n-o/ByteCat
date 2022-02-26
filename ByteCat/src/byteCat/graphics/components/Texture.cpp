#include "bcpch.h"
#include "byteCat/graphics/components/Texture.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLTexture2D.h"
#include "platform/openGL/OpenGLTexture3D.h"

namespace BC
{
	std::shared_ptr<Texture2D> Texture2D::Create(unsigned int width, unsigned int height, const TextureFormat& format)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLTexture2D>(width, height, format);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filePath, float mipmapLOD)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLTexture2D>(filePath, TextureFormat::AUTO, mipmapLOD);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filePath, const TextureFormat& format, float mipmapLOD)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLTexture2D>(filePath, format, mipmapLOD);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	std::shared_ptr<Texture3D> Texture3D::Create(unsigned width, unsigned height, unsigned depth, const TextureFormat& format)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLTexture3D>(width, height, depth, format);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
