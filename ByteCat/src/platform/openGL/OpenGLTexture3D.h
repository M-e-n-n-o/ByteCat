#pragma once
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLTexture3D : public Texture3D
		{
		private:
			unsigned int m_id;

			int m_width;
			int m_height;
			int m_depth;
			int m_channels;
			TextureFormat m_format;

		public:
			OpenGLTexture3D(unsigned int width, unsigned int height, unsigned int depth, const TextureFormat& format);
			~OpenGLTexture3D();
			
			void bind(unsigned textureUnit) const override;
			
			unsigned getWidth() const override { return m_width; }
			unsigned getHeight() const override { return m_height; }
			unsigned getDepth() const override { return m_depth; }
			unsigned getChannels() const override { return m_channels; }
			TextureFormat getFormat() const override { return m_format; }
			unsigned getId() const override { return m_id; }
		};
	}
}
