#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "byteCat/graphics/renderer/RendererAPI.h"
#include "byteCat/graphics/renderer/RenderPass.h"
#include "byteCat/graphics/components/FrameBuffer.h"
#include "byteCat/graphics/components/Texture.h"

namespace BC
{
	namespace Graphics
	{
		class ShadowPass : public RenderPass
		{
		private:
			const unsigned int SHADOW_WIDTH = 1024;
			const unsigned int SHADOW_HEIGHT = 1024;

			RendererAPI* m_rendererAPI;

			std::shared_ptr<FrameBuffer> m_shadowFrameBuffer;
			std::shared_ptr<Texture2D> m_shadowMap;

			std::shared_ptr<Shader> m_depthShader;

			std::shared_ptr<Renderable> m_debugRenderable;

		public:
			ShadowPass() : RenderPass("ShadowPass") {}

			void init(RendererAPI* rendererAPI) override
			{
				m_rendererAPI = rendererAPI;

				m_depthShader = Shader::Create("Shadow depth shader", "DepthShaderVertex.glsl", "DepthShaderFragment.glsl", true);				

				m_shadowFrameBuffer = FrameBuffer::Create("Shadow map", SHADOW_WIDTH, SHADOW_HEIGHT);

				m_shadowMap = Texture2D::Create(SHADOW_WIDTH, SHADOW_HEIGHT, TextureFormat::DEPTH16);
				m_shadowFrameBuffer->attachTexture(m_shadowMap);

				m_shadowFrameBuffer->disableReadWrite();
				m_shadowFrameBuffer->unbind();

				auto debugShader = Shader::Create("Debug depth shader", "DebugDepthVertex.glsl", "DebugDepthFragment.glsl", true);
				debugShader->setTextureSlots({ "depthMap" });

				float dataQuad[] =
				{
				   -1.0f,  1.0f,	0, 1,
				   -1.0f, -1.0f,	0, 0,
					1.0f, -1.0f,	1, 0,
					1.0f,  1.0f,	1, 1
				};

				unsigned indicesQuad[] =
				{
				   0, 1, 2,
				   2, 3, 0
				};

				auto debugVAO = VertexArray::Create();
				auto quadVertexBuffer = VertexBuffer::Create(dataQuad, sizeof(dataQuad));
				quadVertexBuffer->setLayout({ {ShaderDataType::Float2, "vertexPos"}, {ShaderDataType::Float2, "texCoord"} });
				debugVAO->addVertexBuffer(quadVertexBuffer);
				auto quadIndexBuffer = IndexBuffer::Create(indicesQuad, sizeof(indicesQuad));
				debugVAO->setIndexBuffer(quadIndexBuffer);

				std::vector<std::shared_ptr<Texture>> textures = { m_shadowMap };
				m_debugRenderable = std::make_shared<Renderable>(CullingMode::Back, debugVAO, debugShader, textures, glm::mat4(1));
			}

			void execute(std::vector<std::shared_ptr<Renderable>>& renderables, std::shared_ptr<CameraData>& cameraData, std::shared_ptr<LightingData>& lightingData) override
			{
				glm::vec3 lightPos = glm::vec3(0, 5, -5);
				glm::mat4 lightProjection, lightView;
				glm::mat4 lightSpaceMatrix;
				float near_plane = 1.0f, far_plane = 10.0f;
				lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
				lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				//lightSpaceMatrix = cameraData->projectionMatrix * cameraData->viewMatrix;
				lightSpaceMatrix = lightProjection * lightView;

				m_depthShader->bind();
				m_depthShader->loadMatrix4("lightSpaceMatrix", lightSpaceMatrix);

				m_rendererAPI->setViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
				m_shadowFrameBuffer->bind();
				m_rendererAPI->clearBuffers();

				for (const auto& renderable : renderables)
				{
					m_depthShader->loadMatrix4("model", renderable->modelMatrix);

					int unit = 0;
					for (auto& texture : renderable->textures)
					{
						texture->bind(unit++);
					}

					renderable->vao->bind();

					if (renderable->onRender != nullptr)
					{
						renderable->onRender(renderable);
					}

					RendererAPI::SetCullingMode(renderable->cullingMode);

					m_rendererAPI->draw(renderable->vao);
				}

				renderables.clear();

				m_shadowFrameBuffer->unbind();

				auto& window = App::Application::GetInstance().getWindow();
				m_rendererAPI->setViewport(0, 0, window.getWidth(), window.getHeight());

				Renderer::Submit(m_debugRenderable);
			}
		};
	}
}