#pragma once

#include <GL/glew.h>

namespace BC
{
	class ShaderProgram
	{
	private:
		bool isInit = false;
		
	protected:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

	public:
		ShaderProgram(std::string& vertexShader, std::string& fragmentShader);
		virtual ~ShaderProgram() { cleanUp(); }

		void init();
		void start() const;
		void stop() const;
		void cleanUp() const;
	
	protected:
		virtual void bindAttributes() = 0;
		void bindAttribute(int attribute, std::string variableName) const;

		virtual void getAllUniformLocations() = 0;
		unsigned int getUniformLocation(const GLchar* uniformName) const;

	private:
		int loadShader(std::string& shader, int type);
	};
}