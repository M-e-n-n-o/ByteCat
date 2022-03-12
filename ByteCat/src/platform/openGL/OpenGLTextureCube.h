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

			unsigned int m_channels;
			TextureFormat m_format;
			
			std::vector<std::shared_ptr<Texture2D>> m_textureSides;

		public:
			OpenGLTextureCube(const std::vector<std::string>& textures, const TextureFormat& format);
			~OpenGLTextureCube();

			void bind(unsigned textureUnit) const override;

			unsigned getChannels() const override { return m_channels; }
			TextureFormat getFormat() const override { return m_format; }
			
			unsigned getId() const override { return m_id; }

			const std::vector<std::shared_ptr<Texture2D>>& getTextures() override { return m_textureSides; }
		};
	}
}
