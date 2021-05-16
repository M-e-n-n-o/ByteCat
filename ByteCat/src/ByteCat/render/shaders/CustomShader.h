#pragma once

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "byteCat/render/shaders/ShaderProgram.h"

namespace BC
{
	union ShaderUniformVariableValue
	{
		float Float;
		int Int;
		glm::vec2 Vector2;
		glm::vec3 Vector3;
		glm::vec4 Vector4;
		glm::mat4 Matrix4;
	};

	enum class ShaderUniformVariableType
	{
		Float,
		Int,
		Vector2,
		Vector3,
		Vector4,
		Matrix4
	};

	struct ShaderUniformVariable
	{
		std::string variableName;
		ShaderUniformVariableType type;
		ShaderUniformVariableValue value;
	};
	
	
	class CustomShader : public ShaderProgram
	{
	private:
		std::vector<ShaderUniformVariable> vertexVariables;
		std::vector<ShaderUniformVariable> fragmentVariables;
		
	public:
		CustomShader(std::string& vertexShader, std::string& fragmentShader);

		void loadUniformVariable(std::string& variableName, ShaderUniformVariableValue value);

	private:
		std::vector<ShaderUniformVariable> getUniformVariables(std::string& shader);
	
	protected:
		void bindAttributes() override;
	};
}