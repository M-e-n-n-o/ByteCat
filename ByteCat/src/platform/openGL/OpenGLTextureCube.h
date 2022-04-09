#pragma once
#include <vector>
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLTextureCube : public TextureCube
		{
		private:
			unsigned int m_id;

			int m_channels;
			TextureFormat m_format;

		public:
			OpenGLTextureCube(const std::vector<std::string>& faces, const TextureFormat& format);
			~OpenGLTextureCube();

			void bind(unsigned textureUnit) const override;

			unsigned getChannels() const override { return m_channels; }
			TextureFormat getFormat() const override { return m_format; }
			
			unsigned getId() const override { return m_id; }
		};
	}
}