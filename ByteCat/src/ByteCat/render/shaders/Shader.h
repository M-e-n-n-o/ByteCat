#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace BC
{
	// union ShaderUniformVariableValue
	// {
	// 	float Float;
	// 	int Int;
	// 	glm::vec2 Vector2;
	// 	glm::vec3 Vector3;
	// 	glm::vec4 Vector4;
	// 	glm::mat4 Matrix4;
	// };
	//
	// enum class ShaderUniformVariableType
	// {
	// 	Float,
	// 	Int,
	// 	Vector2,
	// 	Vector3,
	// 	Vector4,
	// 	Matrix4,
	// 	Unknown
	// };
	//
	// struct ShaderUniformVariable
	// {
	// 	std::string name;
	// 	ShaderUniformVariableType type;
	// 	unsigned int location;
	// };
	
	
	class Shader
	{
	private:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

		std::function<void()> setTexturesFunc;
		
		//std::vector<ShaderUniformVariable> uniformVariables;
	
	public:
		Shader(std::string& vertexShader, std::string& fragmentShader, std::function<void()> setTextures);
		~Shader();

		void bind() const { glUseProgram(programID); }
		void unbind() const { glUseProgram(0); }
		
		//void loadUniformVariable(std::string variableName, ShaderUniformVariableValue value);
		void loadFloat(std::string name, float value) const;
		void loadInt(std::string name, int value) const;
		void loadVector2(std::string name, glm::vec2 value) const;
		void loadVector3(std::string name, glm::vec3 value) const;
		void loadVector4(std::string name, glm::vec4 value) const;
		void loadMatrix4(std::string name, glm::mat4 value) const;

		void setTextures() const { setTexturesFunc(); }

	private:
		//void getAllUniformLocations();
		int getUniformLocation(const GLchar* uniformName) const;

		void bindAttributes();
		void bindAttribute(int attribute, std::string variableName) const;

		int loadShader(std::string& shader, int type) const;
	};
}