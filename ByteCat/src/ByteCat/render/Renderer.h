#pragma once

#include <memory>
#include <vector>
#include "glm/mat4x4.hpp"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/render/vertex-object/VertexArray.h"

namespace BC
{
	struct SceneData
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	struct Entity
	{
		const std::shared_ptr<Shader> shader;
		const std::shared_ptr<VertexArray> vao;
		const glm::mat4 transformation;
		
		bool operator==(const Entity& other) const
		{
			return vao->getId() == other.vao->getId();
		}
	};
	
	class Renderer
	{
	private:
		static const int ALLOCATE_PER_RESIZE = 20;

		static inline glm::vec4 CLEAR_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };
		
		static std::unique_ptr<SceneData> sceneData;
		static inline std::vector<Entity> entities;

	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(unsigned int width, unsigned int height);

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao, const glm::mat4& transformation = glm::mat4(1.0f));

		static void SetClearColor(glm::vec4& color) { CLEAR_COLOR = color; }
	};
}
