#pragma once

namespace BC
{	
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void loadData(const void* data, unsigned int size, unsigned int offset) = 0;

		virtual const std::string& getName() const = 0;
		virtual unsigned int getBindingIndex() const = 0;
		
		static std::shared_ptr<UniformBuffer> Create(const std::string& blockName, unsigned int bindingIndex, unsigned int size);
		static std::shared_ptr<UniformBuffer> Create(const std::string& blockName, unsigned int bindingIndex, unsigned int size, const void* data);

		
		class Builder
		{
		private:
			const int MAX_BUFFER_SIZE = 800;
			
			std::shared_ptr<UniformBuffer> m_buffer;
			unsigned int m_offset = 0;
			
		public:
			Builder(const std::string& blockName, unsigned int bindingIndex);

			Builder& addInt(const std::string& name, int value);
			
			Builder& addFloat(const std::string& name, float value);

			std::shared_ptr<UniformBuffer> build();
		};
	};
}
