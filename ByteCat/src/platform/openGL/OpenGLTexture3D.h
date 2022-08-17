#pragma once
#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLTexture3D : public Graphics::Texture3D
		{
		private:
			unsigned int m_id;

			int m_width;
			int m_height;
			int m_depth;
			int m_channels;
			Graphics::TextureFormat m_format;

		public:
			OpenGLTexture3D(unsigned int width, unsigned int height, unsigned int depth, const Graphics::TextureFormat& format);
			~OpenGLTexture3D();
			
			void bind(unsigned textureUnit) const override;
			
			unsigned getWidth() const override { return m_width; }
			unsigned getHeight() const override { return m_height; }
			unsigned getDepth() const override { return m_depth; }
			unsigned getChannels() const override { return m_channels; }
			Graphics::TextureFormat getFormat() const override { return m_format; }
			unsigned getId() const override { return m_id; }
		};
	}
}
#endif