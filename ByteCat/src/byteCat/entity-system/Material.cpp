#include "bcpch.h"
#include "byteCat/entity-system/Material.h"

namespace BC
{
	Material::Material(ByteCatShader const& shaderType): ObjectComponent()
	{
		shader = Shaders::Create(shaderType);
	}

	Material::Material(std::shared_ptr<Shader> shader): ObjectComponent()
	{
		this->shader = shader;
	}

	Material::Material(std::string& vertexShader, std::string& fragmentShader): ObjectComponent()
	{
		shader = Shader::Create(vertexShader, fragmentShader);
	}
}
