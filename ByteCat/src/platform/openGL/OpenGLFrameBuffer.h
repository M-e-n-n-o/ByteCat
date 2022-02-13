#pragma once
#include "byteCat/graphics/components/FrameBuffer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLFrameBuffer : public FrameBuffer
		{
		private:
			unsigned int m_id;
		
		public:
			OpenGLFrameBuffer();
			~OpenGLFrameBuffer();

			void bind() const override;
			void unbind() const override;
		};
	}
}
