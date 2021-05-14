#pragma once

namespace BC
{
	class ShaderProgram
	{
	private:
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

	private:
		int loadShader(std::string& shader, int type);
	};
}