#pragma once

#include <string>

namespace BC
{
	class Texture
	{
	protected:
		unsigned int textureID;
		unsigned int width;
		unsigned int height;
		unsigned int bpp;
	
	public:		
		virtual ~Texture() = default;

		unsigned int getID() const { return textureID; }
		
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getBpp() const = 0;
		
		virtual void bind(unsigned int textureUnit = 0) const = 0;
	};

	
	class Texture2D : public Texture
	{
	public:
		Texture2D(std::string& filePath);
		~Texture2D() override;
		
		unsigned int getWidth() const override { return width; }
		unsigned int getHeight() const override { return height; }
		unsigned int getBpp() const override { return bpp; }
		
		void bind(unsigned int textureUnit = 0) const override;

		static std::shared_ptr<Texture2D> Create(std::string filePath)
		{
			return std::make_shared<Texture2D>(filePath);
		}
	};
}
