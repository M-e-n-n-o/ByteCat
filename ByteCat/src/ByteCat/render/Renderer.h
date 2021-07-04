#pragma once

#include <memory>
#include <vector>
#include "glm/mat4x4.hpp"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/render/vertex-object/VertexArray.h"

namespace BC
{
	// This structs holds all the generic scene data for a single render
	struct SceneData
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	// This struct represents a VertexArray with a transformation and shader to render itself with.
	struct Entity
	{
		const std::shared_ptr<Shader> shader;
		const std::shared_ptr<VertexArray> vao;
		const glm::mat4 modelMatrix;
		
		bool operator==(const Entity& other) const
		{
			return vao->getId() == other.vao->getId();
		}
	};

	/*
	 * Class Renderer:
	 *		this class saves all data for a render and renders when all data is in.
	 */
	class Renderer
	{
	private:
		static const int ALLOCATE_PER_RESIZE = 20;
		static inline int drawCalls = 0;
		
		static inline glm::vec4 CLEAR_COLOR = { 0.5f, 0.5f, 0.5f, 1.0f };
		
		static std::unique_ptr<SceneData> sceneData;
		static inline std::vector<Entity> entities;

	public:
		static void Init();
		static void Shutdown();

		// Call this function to change the size of the window
		static void OnWindowResize(unsigned int width, unsigned int height);

		// Call this function before submitting entity's to the renderer
		static void BeginScene();
		// This function renders all the submitted entity's in a efficient way
		static void EndScene();

		// Call this function to submit an entity to render on the window
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao, const glm::mat4& modelMatrix = glm::mat4(1.0f));

		static void SetClearColor(glm::vec4& color) { CLEAR_COLOR = color; }

		static int GetNumberOfDrawCalls() { return drawCalls; }
	
	private:
		static void Render(const std::shared_ptr<VertexArray>& vao);
	};
}
