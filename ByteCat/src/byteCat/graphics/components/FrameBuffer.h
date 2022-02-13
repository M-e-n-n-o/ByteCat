#pragma once
#include <memory>

namespace BC
{	
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;
		
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static std::shared_ptr<FrameBuffer> Create();
	};
}