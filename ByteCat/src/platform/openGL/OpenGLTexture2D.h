#pragma once
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{		
		class OpenGLTexture2D : public Texture2D
		{
		private:
			unsigned int m_id;
			
			int m_width;
			int m_height;
			int m_channels;
			TextureFormat m_format;

			// unsigned char* m_textureData = nullptr;
			
		public:
			OpenGLTexture2D(unsigned int width, unsigned int height, const TextureFormat& format);
			OpenGLTexture2D(const std::string& filePath, const TextureFormat& format, float mipmapLOD);
			~OpenGLTexture2D();

			void bind(unsigned textureUnit) const override;

			unsigned getWidth() const override { return m_width; }
			unsigned getHeight() const override { return m_height; }
			unsigned getChannels() const override { return m_channels; }
			TextureFormat getFormat() const override { return m_format; }
			unsigned getId() const override { return m_id; }

			// unsigned char* getTextureData() const override { return m_textureData; }
			// unsigned char getValue(unsigned channel, unsigned x, unsigned y) const override;
		};
	}
}
