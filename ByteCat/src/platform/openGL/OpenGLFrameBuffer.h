#pragma once
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

			unsigned int m_renderBufferId;
		
		public:
			OpenGLFrameBuffer(const std::string& name, unsigned width, unsigned height);
			~OpenGLFrameBuffer();

			void bind() const override;
			void unbind() const override;

			bool isComplete() const override;
			
			void attachTexture(std::shared_ptr<Graphics::Texture2D> texture, unsigned int slot) override;
			void attachRenderBuffer(const Graphics::TextureFormat& format) override;
		};
	}
}
