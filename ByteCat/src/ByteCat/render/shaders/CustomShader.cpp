#include "bcpch.h"
#include "byteCat/render/shaders/CustomShader.h"

namespace BC
{
	CustomShader::CustomShader(std::string& vertexShader, std::string& fragmentShader) : ShaderProgram(vertexShader, fragmentShader)
	{
		vertexVariables = getUniformVariables(vertexShader);
		fragmentVariables = getUniformVariables(fragmentShader);
	}

	void CustomShader::loadUniformVariable(std::string& variableName, ShaderUniformVariableValue value)
	{
		// Find the right uniform variable and load the value
	}

	std::vector<ShaderUniformVariable> CustomShader::getUniformVariables(std::string& shader)
	{
		// Get all the uniform variables from the shader and return them
	}
}
