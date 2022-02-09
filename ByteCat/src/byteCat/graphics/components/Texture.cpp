#include "bcpch.h"
#include "byteCat/graphics/components/Texture.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLTexture2D.h"

namespace BC
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& fileName, float mipmapLod)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<OpenGLTexture2D>(fileName, mipmapLod);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
