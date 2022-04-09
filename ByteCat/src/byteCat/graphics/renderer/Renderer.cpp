#include "bcpch.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/app/Application.h"
#include "byteCat/utils/Math.h"
#include "glm/ext/matrix_clip_space.hpp"

namespace BC
{
	static const std::string vertexShader = R"(
		#version 330 core

		layout (location = 0) in vec3 VertexPos;
		layout (location = 1) in vec2 TexCoord;

		out vec2 PassTexCoord;
	
		uniform mat4 _modelMatrix;
		uniform mat4 _projectionMatrix;

		void main()
		{
			PassTexCoord = TexCoord;
			gl_Position = _projectionMatrix * _modelMatrix * vec4(VertexPos, 1.0);
		}
	)";

	static const std::string fragmentShader = R"(
		#version 330 core

		in vec2 PassTexCoord;
		
		out vec4 FragColor;

		uniform sampler2D tex;
		uniform bool useTex;
	
		uniform vec4 color;

		void main()
		{
			vec4 col = color;

			if (useTex)
			{
				col *= texture(tex, PassTexCoord);
			}
	
			FragColor = col;
		}
	)";

	inline static std::shared_ptr<Shader> basicShader = nullptr;
	inline static std::shared_ptr<VertexArray> basicVao = nullptr;

	static void InitBasicGraphics()
	{
		basicShader = Shader::Create("Basic 2D shader", vertexShader, fragmentShader, false);
		basicShader->setTextureSlots({ "tex" });

		basicVao = VertexArray::Create();
		
		float data[] =
		{
			 // Positions		  // Texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f
		};

		auto vbo = VertexBuffer::Create(data, sizeof(data));
		vbo->setLayout({ {ShaderDataType::Float3, "VertexPos"}, {ShaderDataType::Float2, "TexCoord"} });
		basicVao->addVertexBuffer(vbo);

		unsigned int indices[] =
		{
			0, 2, 1,
			2, 0, 3
		};
		
		auto ebo = IndexBuffer::Create(indices, sizeof(indices));
		basicVao->setIndexBuffer(ebo);
	};
	
	
	#define CHECK_INIT if(!s_isInit) { LOG_ERROR("The renderer has not been initialized yet!"); return; }

	void Renderer::SetAPI(const GraphicsAPI& api)
	{
		if (s_graphicsAPI == GraphicsAPI::None)
		{
			s_graphicsAPI = api;
		}
	}
	
	void Renderer::Init()
	{
		if (s_graphicsAPI == GraphicsAPI::None)
		{
			LOG_ERROR("Set the graphics API before initializing the renderer!");
			return;
		}

		if (!s_isInit)
		{
			s_rendererAPI = RendererAPI::Create(s_graphicsAPI);

			InitBasicGraphics();
			
			s_isInit = true;
		}
	}

	void Renderer::SetSubmissionRenderer(SubmissionRenderer* renderer)
	{
		if (renderer == nullptr)
		{
			delete renderer;
			return;
		}

		if (!s_isInit)
		{
			LOG_ERROR("Initialize the renderer before setting the submission renderer!");
			delete renderer;
			return;
		}

		if (!renderer->supports(s_graphicsAPI))
		{
			LOG_ERROR("Submission renderer: {0} does not support the selected graphics API!", renderer->getName());
			delete renderer;
			return;
		}
		
		delete s_submissionRenderer;
		s_submissionRenderer = renderer;
		s_submissionRenderer->init(s_rendererAPI);

		s_hasRenderer = true;
	}

	void Renderer::Shutdown()
	{
		delete s_rendererAPI;
		delete s_submissionRenderer;
	}

	void Renderer::SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
	{
		CHECK_INIT

		s_rendererAPI->setViewport(x, y, width, height);
	}

	void Renderer::Clear(const glm::vec4& color)
	{
		CHECK_INIT
		
		s_rendererAPI->clearColor(color);
		s_rendererAPI->clearBuffers();
	}

	void Renderer::SetColor(const glm::vec4& color)
	{
		CHECK_INIT

		basicShader->bind();
		basicShader->loadVector4("color", color);
	}

	void Renderer::DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& scale)
	{
		CHECK_INIT

		const glm::mat4 modelMatrix = Math::CreateModelMatrix({position.x, position.y, -1}, { 0, 0, rotation }, {scale.x, scale.y, 1});

		auto& window = Application::GetInstance().getWindow();
		float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);
		
		basicShader->bind();
		basicShader->loadInt("useTex", false);
		basicShader->loadMatrix4("_modelMatrix", modelMatrix);
		basicShader->loadMatrix4("_projectionMatrix", glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, 0.01f, 10.0f));

		basicVao->bind();
		s_rendererAPI->draw(basicVao);
	}

	void Renderer::DrawImage(const glm::vec2& position, float rotation, const glm::vec2& scale, const  std::shared_ptr<Texture2D>& texture)
	{
		CHECK_INIT

		const glm::mat4 modelMatrix = Math::CreateModelMatrix({ position.x, position.y, -1 }, { 0, 0, rotation }, { scale.x, scale.y, 1 });

		auto& window = Application::GetInstance().getWindow();
		float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);

		basicShader->bind();
		basicShader->loadInt("useTex", true);
		basicShader->loadMatrix4("_modelMatrix", modelMatrix);
		basicShader->loadMatrix4("_projectionMatrix", glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, 0.01f, 10.0f));

		texture->bind(0);
		
		basicVao->bind();
		s_rendererAPI->draw(basicVao);
	}

	void Renderer::Submit(const Renderable& renderable)
	{
		CHECK_INIT

		if (!s_hasRenderer)
		{
			LOG_ERROR("No submission renderer has been set!");
			return;
		}
		
		s_submissionRenderer->submit(renderable);
	}

	void Renderer::SetSceneData(const SceneData& sceneData)
	{
		CHECK_INIT

		if (!s_hasRenderer)
		{
			LOG_ERROR("No submission renderer has been set!");
			return;
		}

		s_submissionRenderer->setSceneData(sceneData);
	}

	void Renderer::RenderSubmissions()
	{
		CHECK_INIT

		if (!s_hasRenderer)
		{
			return;
		}
		
		s_submissionRenderer->renderSubmissions();
	}
}
