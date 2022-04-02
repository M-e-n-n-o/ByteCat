#pragma once
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	struct Renderable
	{
		CullingMode cullingMode;
		// RenderLayer renderLayer;
		
		std::shared_ptr<VertexArray> vao;
		std::shared_ptr<Shader> shader;

		// Put in order of texture unit!
		std::vector<std::shared_ptr<Texture>> textures;
		
		glm::mat4 modelMatrix;

		std::function<void(const Renderable&)> onRender;
	};


	struct SceneData
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};
}
