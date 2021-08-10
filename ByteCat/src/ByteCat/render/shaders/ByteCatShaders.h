#pragma once

#include <string>
#include "byteCat/render/shaders/Shader.h"

namespace BC
{
	// This enum holds all the names of each predefined ByteCat shader
	enum class ByteCatShader
	{
		Standard
	};	
	
	class StandardShader: public Shader
	{
	private:		
		static const std::string vertexShader;
		static const std::string fragmentShader;

	public:
		StandardShader();

		static std::shared_ptr<Shader> Create()
		{		
			return std::static_pointer_cast<Shader>(std::make_shared<StandardShader>());
		}
	};

	namespace Shaders
	{
		// Use this function to create a predefined ByteCat shader
		static std::shared_ptr<Shader> Create(ByteCatShader const& shaderType)
		{
			switch (shaderType)
			{
			case ByteCatShader::Standard: return StandardShader::Create();
			}

			LOG_ERROR("ByteCat shadertype \"{0}\" not found", shaderType);
			return Shader::Create(std::string("ERROR"), std::string("ERROR"));
		}
	}
}
