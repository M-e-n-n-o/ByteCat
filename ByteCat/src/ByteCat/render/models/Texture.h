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
	
	public:		
		virtual ~Texture() = default;

		unsigned int getID() const { return textureID; }
		
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		
		virtual void bind(unsigned int number = 0) const = 0;
	};

	
	class Texture2D : public Texture
	{
	public:
		Texture2D(std::string filePath);
		~Texture2D() override;
		
		unsigned int getWidth() const override { return width; }
		unsigned int getHeight() const override { return height; }
		
		void bind(unsigned int number = 0) const override;
	};
}
