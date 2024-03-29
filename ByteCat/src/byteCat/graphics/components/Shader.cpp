#include "bcpch.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/renderer/Renderer.h"

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
	#include "platform/openGL/OpenGLComputeShader.h"
	#include "platform/openGL/OpenGLShader.h"
#endif

namespace BC
{
	namespace Graphics
	{
		std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, bool isFilePath)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:			LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
			case GraphicsAPI::OpenGL:
			case GraphicsAPI::OpenGLES:		return std::make_shared<Platform::OpenGLShader>(name, vertexSrc, fragmentSrc, isFilePath);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}

		std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc, bool isFilePath)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:			LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
			case GraphicsAPI::OpenGL:		return std::make_shared<Platform::OpenGLShader>(name, vertexSrc, geometrySrc, fragmentSrc, isFilePath);
			case GraphicsAPI::OpenGLES:		LOG_ERROR("Geometry shader is not supported on OpenGLES"); return nullptr;
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}

		std::shared_ptr<ComputeShader> ComputeShader::Create(const std::string& name, const std::string& computeSrc,
			bool isFilePath)
		{
			switch (Renderer::GetAPI())
			{
			case GraphicsAPI::None:			LOG_CRITICAL("No Graphics API selected!"); return nullptr;

#ifdef BC_PLATFORM_PC
			case GraphicsAPI::OpenGL:		return std::make_shared<Platform::OpenGLComputeShader>(name, computeSrc, isFilePath);
#endif
			}

			LOG_CRITICAL("Unsupported Graphics API selected!");
			return nullptr;
		}
	}
}
