#pragma once
#include "glm/vec4.hpp"
#include "byteCat/graphics/components/VertexArray.h"
#include "byteCat/graphics/renderer/RenderModes.h"

namespace BC
{
	namespace Graphics
	{
		enum class GraphicsAPI
		{
			None = 0,
			
			OpenGL,
			OpenGLES
		};


		/**
		 * @brief
		 * This generic RendererAPI directs requests to the native RendererAPI (for example: OpenGL)
		 */
		class RendererAPI
		{
		private:
			inline static RendererAPI* s_instance = nullptr;

		public:
			virtual ~RendererAPI() = default;

			virtual void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
			virtual void clearColor(const glm::vec4& color) = 0;
			virtual void clearBuffers() = 0;
			virtual void draw(std::shared_ptr<VertexArray> vao, unsigned int indexCount = 0) = 0;

			static void SetCullingMode(const CullingMode& mode);

			static RendererAPI* Create(const GraphicsAPI& api);

		private:
			virtual void setCullingMode(const CullingMode& mode) = 0;
		};
	}
}
