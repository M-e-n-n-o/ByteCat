#pragma once
#if defined(BC_PLATFORM_PC) || defined(BC_PLATFORM_MOBILE)
#include "byteCat/graphics/components/FrameBuffer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLFrameBuffer : public Graphics::FrameBuffer
		{
		private:
			unsigned int m_id;

			std::string m_name;
			unsigned int m_width;
			unsigned int m_height;

			unsigned int m_colorAttachmentSlot = 0;

			unsigned int m_renderBufferId;
		
		public:
			OpenGLFrameBuffer(const std::string& name, unsigned width, unsigned height);
			~OpenGLFrameBuffer();

			void bind() const override;
			void unbind() const override;

			bool isComplete() const override;
			
			void disableReadWrite() const override;

			void attachTexture(std::shared_ptr<Graphics::Texture2D> texture) override;
			void attachRenderBuffer(const Graphics::TextureFormat& format) override;
		};
	}
}
#endif