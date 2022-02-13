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
		RGB,
		RGBA
	};
	
	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual void bind(unsigned int textureUnit = 0) const = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getChannels() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual void bind(unsigned textureUnit) const override = 0;
		
		virtual unsigned getWidth() const override = 0;
		virtual unsigned getHeight() const override = 0;
		virtual unsigned getChannels() const override = 0;
		
		static std::shared_ptr<Texture2D> Create(const std::string& filePath, float mipmapLOD = 0);
		static std::shared_ptr<Texture2D> Create(const std::string& filePath, const TextureFormat& format, float mipmapLOD = 0);
	};
}
