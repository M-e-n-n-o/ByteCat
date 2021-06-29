#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace BC
{	
	class Shader
	{
	private:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

		bool hasTextures;

		std::function<void()> bindTexturesFunc;
	
	public:
		Shader(std::string& vertexShader, std::string& fragmentShader);
		virtual ~Shader();

		void bind() const { glUseProgram(programID); }
		void unbind() const { glUseProgram(0); }
		
		void loadFloat(std::string name, float value) const;
		void loadInt(std::string name, int value) const;
		void loadVector2(std::string name, glm::vec2 value) const;
		void loadVector3(std::string name, glm::vec3 value) const;
		void loadVector4(std::string name, glm::vec4 value) const;
		void loadMatrix4(std::string name, glm::mat4 value) const;

		void setTextures(std::function<void()> func) { bindTexturesFunc = func; }
		void bindTextures() const;

	private:
		int getUniformLocation(const GLchar* uniformName) const;

		void bindAttributes();
		void bindAttribute(int attribute, std::string variableName) const;

		int loadShader(std::string& shader, int type) const;
	};
}
