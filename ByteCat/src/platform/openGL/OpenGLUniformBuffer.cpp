#include "bcpch.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "platform/openGL/OpenGLUniformBuffer.h"

namespace BC
{
	namespace Platform
	{
		#define CHECK_LAYOUT LOG_WARN("UniformBuffer {0} has no layout!", blockName); if (layout.getElements().empty()) { return; }
		
		OpenGLUniformBuffer::OpenGLUniformBuffer(const std::string& blockName, unsigned bindingIndex): blockName(blockName), bindingIndex(bindingIndex)
		{
			glGenBuffers(1, &id);
		}

		OpenGLUniformBuffer::~OpenGLUniformBuffer()
		{
			glDeleteBuffers(1, &id);
		}

		void OpenGLUniformBuffer::bind() const
		{
			glBindBuffer(GL_UNIFORM_BUFFER, id);
		}

		void OpenGLUniformBuffer::unbind() const
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		void OpenGLUniformBuffer::setLayout(const BufferLayout& layout)
		{			
			this->layout = layout;

			bind();

			unsigned int size = 0;
			for (const auto& element : layout)
			{
				size += element.size;
			}
			
			glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, id);
		}

		void OpenGLUniformBuffer::loadInt(const std::string& name, int value)
		{
			CHECK_LAYOUT
			
			unsigned int size, offset;
			bool found = getSizeAndOffset(name, ShaderDataType::Int, size, offset);
			if (!found) { return; }
			
			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, (void*) value);
		}

		void OpenGLUniformBuffer::loadFloat(const std::string& name, float value)
		{
			CHECK_LAYOUT

			unsigned int size, offset;
			bool found = getSizeAndOffset(name, ShaderDataType::Float, size, offset);
			if (!found) { return; }

			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, (void*) &value);
		}

		void OpenGLUniformBuffer::loadVector2(const std::string& name, const glm::vec2& value)
		{
			CHECK_LAYOUT

			unsigned int size, offset;
			bool found = getSizeAndOffset(name, ShaderDataType::Float2, size, offset);
			if (!found) { return; }

			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(value));
		}

		void OpenGLUniformBuffer::loadVector3(const std::string& name, const glm::vec3& value)
		{
			CHECK_LAYOUT

			unsigned int size, offset;
			bool found = getSizeAndOffset(name, ShaderDataType::Float3, size, offset);
			if (!found) { return; }

			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(value));
		}

		void OpenGLUniformBuffer::loadVector4(const std::string& name, const glm::vec4& value)
		{
			CHECK_LAYOUT

			unsigned int size, offset;
			bool found = getSizeAndOffset(name, ShaderDataType::Float4, size, offset);
			if (!found) { return; }

			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(value));
		}

		void OpenGLUniformBuffer::loadMatrix4(const std::string& name, const glm::mat4& value)
		{
			CHECK_LAYOUT

			unsigned int size, offset;
			bool found = getSizeAndOffset(name, ShaderDataType::Mat4, size, offset);
			if (!found) { return; }

			bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, glm::value_ptr(value));
		}

		bool OpenGLUniformBuffer::getSizeAndOffset(const std::string& name, const ShaderDataType& type, unsigned& size, unsigned& offset)
		{
			for (const auto& element : layout)
			{				
				if (element.name == name)
				{
					if (element.type == type)
					{
						size = element.size;
						offset = element.offset;
						return true;
					} else
					{
						LOG_ERROR("The given variable: {0} in UniformBuffer: {1} does not have the right ShaderDataType", name, blockName);
						return false;
					}
				}
			}

			LOG_ERROR("Variable \"{0}\" not found in the UniformBuffer {1}", name, blockName);
			return false;
		}
	}
}
