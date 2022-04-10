#pragma once
#include <vector>
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLTextureCube : public Graphics::TextureCube
		{
		private:
			unsigned int m_id;

			int m_channels;
			Graphics::TextureFormat m_format;

		public:
			OpenGLTextureCube(const std::vector<std::string>& faces, const Graphics::TextureFormat& format);
			~OpenGLTextureCube();

			void bind(unsigned textureUnit) const override;

			unsigned getChannels() const override { return m_channels; }
			Graphics::TextureFormat getFormat() const override { return m_format; }
			
			unsigned getId() const override { return m_id; }
		};
	}
}
