#pragma once

#include "byteCat/entity-system/GameObject.h"

namespace BC
{
	class Sprite : public RenderComponent
	{
	private:
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<Texture2D> texture;

	public:
		Sprite(std::string const& fileName);
		Sprite(std::shared_ptr<Texture2D>& texture);

		void setTexture(std::string const& fileName);
		void setTexture(std::shared_ptr<Texture2D>& texture);

		void onAttach() override;
	
	private:
		void prepareRender(glm::mat4& viewMatrix, glm::mat4& projectionMatrix) override;
		
		std::shared_ptr<VertexArray>& getVao() override { return vao; }
		
		std::shared_ptr<VertexArray> generateVao(unsigned int width, unsigned int height) const;
	};
}
