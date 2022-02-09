#pragma once
#include <memory>
#include <string>

namespace BC
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual void bind(unsigned int textureUnit = 0) const = 0;
		virtual void unbind() const = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getBpp() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual void bind(unsigned textureUnit) const override = 0;
		virtual void unbind() const override = 0;
		
		virtual unsigned getWidth() const override = 0;
		virtual unsigned getHeight() const override = 0;
		virtual unsigned getBpp() const override = 0;
		
		static std::shared_ptr<Texture2D> Create(const std::string& fileName, float mipmapLod);
	};
}
