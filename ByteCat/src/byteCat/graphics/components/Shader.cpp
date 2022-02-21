#include "bcpch.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/openGL/OpenGLShader.h"

namespace BC
{
	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, bool isFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLShader>(name, vertexSrc, fragmentSrc, isFilePath);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}
}
