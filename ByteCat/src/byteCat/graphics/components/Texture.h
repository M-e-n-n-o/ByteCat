#pragma once
#include <memory>
#include <string>

namespace BC
{
	// How should the format of the texture be stored
	enum class TextureFormat
	{
		AUTO = 0,
		
		DEPTH,
		DEPTH_STENCIL,
		
		R,
		RG,
		RGB16F,
		RGBA16F
	};
	
	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual void bind(unsigned int textureUnit = 0) const = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getChannels() const = 0;
		virtual TextureFormat getFormat() const = 0;
		virtual unsigned int getId() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual void bind(unsigned textureUnit) const override = 0;
		
		virtual unsigned getWidth() const override = 0;
		virtual unsigned getHeight() const override = 0;
		virtual unsigned getChannels() const override = 0;
		virtual TextureFormat getFormat() const override = 0;
		virtual unsigned int getId() const override = 0;

		static std::shared_ptr<Texture2D> Create(unsigned int width, unsigned int height, const TextureFormat& format);
		static std::shared_ptr<Texture2D> Create(const std::string& filePath, float mipmapLOD = 0);
		static std::shared_ptr<Texture2D> Create(const std::string& filePath, const TextureFormat& format, float mipmapLOD = 0);
	};

	class Texture3D : public Texture
	{
	public:
		virtual void bind(unsigned textureUnit) const override = 0;

		virtual unsigned getWidth() const override = 0;
		virtual unsigned getHeight() const override = 0;
		virtual unsigned getDepth() const = 0;
		virtual unsigned getChannels() const override = 0;
		virtual TextureFormat getFormat() const override = 0;
		virtual unsigned int getId() const override = 0;

		static std::shared_ptr<Texture3D> Create(unsigned int width, unsigned int height, unsigned int depth, const TextureFormat& format);
	};
}
