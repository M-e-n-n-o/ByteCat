#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "byteCat/render/shaders/ByteCatShaders.h"

namespace BC
{
	class Material : public ObjectComponent
	{
	private:
		std::shared_ptr<Shader> shader;

	public:
		Material(ByteCatShader const& shaderType);
		Material(std::shared_ptr<Shader> shader);
		Material(std::string& vertexShader, std::string& fragmentShader);

		void setShader(std::shared_ptr<Shader> newShader) { shader = newShader; }
		std::shared_ptr<Shader>& getShader() { return shader; }
	};
}
