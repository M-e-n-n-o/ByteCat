#pragma once
#include <memory>
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/components/Shader.h"
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Graphics
	{
		/**
		 * @brief
		 * Use this structure to submit different types of inputs to the renderer
		 */
		struct RendererInput
		{
			RendererInput() = default;
			~RendererInput() = default;

			enum class InputType
			{
				Renderable,
				CameraData
			};

			virtual InputType getInputType() const = 0;
		};

		struct Renderable : RendererInput
		{
			CullingMode cullingMode;
			// RenderLayer renderLayer;

			std::shared_ptr<VertexArray> vao;
			std::shared_ptr<Shader> shader;

			// Put in order of texture unit!
			std::vector<std::shared_ptr<Texture>> textures;

			glm::mat4 modelMatrix;

			std::function<void(const std::shared_ptr<Renderable>&)> onRender;

			Renderable(CullingMode cullingMode,	std::shared_ptr<VertexArray> vao, std::shared_ptr<Shader> shader, 
				std::vector<std::shared_ptr<Texture>> textures, glm::mat4 modelMatrix, std::function<void(const std::shared_ptr<Renderable>&)> onRender = nullptr):
				cullingMode(cullingMode), vao(vao), shader(shader), textures(textures), modelMatrix(modelMatrix), onRender(onRender) {}

			virtual InputType getInputType() const override
			{
				return InputType::Renderable;
			}
		};

		struct CameraData : RendererInput
		{
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;

			CameraData(glm::mat4 viewMatrix, glm::mat4 projectionMatrix): viewMatrix(viewMatrix), projectionMatrix(projectionMatrix) {}

			virtual InputType getInputType() const override
			{
				return InputType::CameraData;
			}
		};
	}
}
