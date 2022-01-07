#pragma once
#include <glm/glm.hpp>
#include "byteCat/graphics/buffers/ArrayBuffer.h"

namespace BC
{
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;

		virtual void loadInt(const std::string& name, int value) = 0;
		virtual void loadFloat(const std::string& name, float value) = 0;
		virtual void loadVector2(const std::string& name, const glm::vec2& value) = 0;
		virtual void loadVector3(const std::string& name, const glm::vec3& value) = 0;
		virtual void loadVector4(const std::string& name, const glm::vec4& value) = 0;
		virtual void loadMatrix4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& getName() const = 0;
		virtual unsigned int getBindingIndex() const = 0;
		
		static std::shared_ptr<UniformBuffer> Create(const std::string& blockName, unsigned int bindingIndex);
	};
}
