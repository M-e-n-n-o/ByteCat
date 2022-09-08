#pragma once
#include <memory>
#include <string>

namespace BC
{
	namespace Graphics
	{
		enum class TextureFormat
		{
			AUTO = 0,

			DEPTH32,
			DEPTH24_STENCIL8,

			R8,
			RG8,
			RGB16F,
			RGBA16F
		};

		class Texture
		{
		public:
			virtual ~Texture() = default;

			virtual void bind(unsigned int textureUnit = 0) const = 0;
			virtual void unbind() const = 0;

			virtual unsigned int getChannels() const = 0;
			virtual TextureFormat getFormat() const = 0;
			virtual unsigned int getId() const = 0;
		};

		class Texture2D : public Texture
		{
		public:
			virtual ~Texture2D() = default;

			virtual void bind(unsigned textureUnit) const override = 0;
			virtual void unbind() const override = 0;

			virtual unsigned getWidth() const = 0;
			virtual unsigned getHeight() const = 0;

			virtual unsigned getChannels() const override = 0;
			virtual TextureFormat getFormat() const override = 0;
			virtual unsigned int getId() const override = 0;

			// virtual unsigned char* getTextureData() const = 0;
			// virtual unsigned char getValue(unsigned channel, unsigned x, unsigned y) const = 0;

			static std::shared_ptr<Texture2D> Create(unsigned int width, unsigned int height, const TextureFormat& format);
			static std::shared_ptr<Texture2D> Create(const std::string& filePath, float mipmapLOD = 0);
			static std::shared_ptr<Texture2D> Create(const std::string& filePath, const TextureFormat& format, float mipmapLOD = 0);
		};

		class Texture3D : public Texture
		{
		public:
			virtual ~Texture3D() = default;

			virtual void bind(unsigned textureUnit) const override = 0;
			virtual void unbind() const override = 0;

			virtual unsigned getWidth() const = 0;
			virtual unsigned getHeight() const = 0;
			virtual unsigned getDepth() const = 0;

			virtual unsigned getChannels() const override = 0;
			virtual TextureFormat getFormat() const override = 0;
			virtual unsigned int getId() const override = 0;

			static std::shared_ptr<Texture3D> Create(unsigned int width, unsigned int height, unsigned int depth, const TextureFormat& format);
		};

		class TextureCube : public Texture
		{
		public:
			virtual ~TextureCube() = default;

			virtual void bind(unsigned int textureUnit) const override = 0;
			virtual void unbind() const override = 0;

			virtual unsigned getChannels() const override = 0;
			virtual TextureFormat getFormat() const override = 0;
			virtual unsigned getId() const override = 0;

			static std::shared_ptr<TextureCube> Create(std::initializer_list<std::string> faces, const TextureFormat& format = TextureFormat::RGB16F);
		};
	}
}
