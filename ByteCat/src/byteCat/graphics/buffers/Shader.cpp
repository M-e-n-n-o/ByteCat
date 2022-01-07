#include "bcpch.h"
#include "byteCat/graphics/buffers/Shader.h"
#include "byteCat/graphics/renderers/Renderer.h"
#include "platform/openGL/OpenGLShader.h"

namespace BC
{
	// --------------------------------------------------------------------
	// --------------------------- Shader ---------------------------------
	// --------------------------------------------------------------------
	
	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case GraphicsAPI::None:		LOG_CRITICAL("No Graphics API selected!"); return nullptr;
		case GraphicsAPI::OpenGL:	return std::make_shared<Platform::OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		LOG_CRITICAL("Unsupported Graphics API selected!");
		return nullptr;
	}

	// --------------------------------------------------------------------
	// ----------------------- Shader Library -----------------------------
	// --------------------------------------------------------------------

	void ShaderPack::add(const std::shared_ptr<Shader>& shader)
	{
		for (auto buffer : ufbs)
		{
			shader->addUniformBuffer(buffer->getName(), buffer->getBindingIndex());
		}

		shaders.push_back(shader);
	}

	std::shared_ptr<Shader> ShaderPack::get(const std::string& name)
	{
		for (auto shader : shaders)
		{
			if (shader->getName() == name)
			{
				return shader;
			}
		}

		return nullptr;
	}

	void ShaderPack::addUniformBuffer(const std::string& bufferName, const BufferLayout& layout)
	{
		int bindingIndex = ufbs.size();
		auto ufb = UniformBuffer::Create(bufferName, bindingIndex);

		
	}
}
