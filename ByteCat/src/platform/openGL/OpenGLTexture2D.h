#pragma once
#ifdef BC_PLATFORM_PC
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{		
		class OpenGLTexture2D : public Graphics::Texture2D
		{
		private:
			unsigned int m_id;
			
			int m_width;
			int m_height;
			int m_channels;
			Graphics::TextureFormat m_format;

			// unsigned char* m_textureData = nullptr;
			
		public:
			OpenGLTexture2D(unsigned int width, unsigned int height, const Graphics::TextureFormat& format);
			OpenGLTexture2D(const std::string& filePath, const Graphics::TextureFormat& format, float mipmapLOD);
			~OpenGLTexture2D();

			void bind(unsigned textureUnit) const override;

			unsigned getWidth() const override { return m_width; }
			unsigned getHeight() const override { return m_height; }
			unsigned getChannels() const override { return m_channels; }
			Graphics::TextureFormat getFormat() const override { return m_format; }
			unsigned getId() const override { return m_id; }

			// unsigned char* getTextureData() const override { return m_textureData; }
			// unsigned char getValue(unsigned channel, unsigned x, unsigned y) const override;
		};
	}
}
#endif