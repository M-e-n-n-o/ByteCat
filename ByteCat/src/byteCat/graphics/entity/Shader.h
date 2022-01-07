#pragma once

#include <string>
#include <glm/glm.hpp>

namespace BC
{
	/// <summary>
	/// This class represents a shader program which is needed to render with a VertexArray.
	/// </summary>
	class Shader
	{	
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void loadInt(const std::string& name, int value) = 0;
		virtual void loadIntArray(const std::string& name, int* values, unsigned int count) = 0;
		virtual void loadFloat(const std::string& name, float value) = 0;
		virtual void loadVector2(const std::string& name, const glm::vec2& value) = 0;
		virtual void loadVector3(const std::string& name, const glm::vec3& value) = 0;
		virtual void loadVector4(const std::string& name, const glm::vec4& value) = 0;
		virtual void loadMatrix4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& getName() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}
