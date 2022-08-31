#include "bcpch.h"
#include "byteCat/graphics/renderer/Renderer2D.h"
#include "byteCat/app/Application.h"
#include "byteCat/utils/Math.h"
#include "glm/ext/matrix_clip_space.hpp"

namespace BC
{
	namespace Graphics
	{
#ifdef BC_PLATFORM_PC
		static const std::string shaderVersion = "#version 330 core";
#elif defined(BC_PLATFORM_MOBILE)
		static const std::string shaderVersion = "#version 300 es";
#endif
		
		static const std::string vertexShader = R"(
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
		in vec2 PassTexCoord;
		
		out vec4 FragColor;

		uniform sampler2D tex;
		uniform bool useTex;
	
		uniform vec4 color;

		void main()
		{
			vec4 col = color;

			col *= mix(col, texture(tex, PassTexCoord), useTex);
	
			FragColor = col;
		}
	)";

		inline static std::shared_ptr<Shader> basicShader = nullptr;
		inline static std::shared_ptr<VertexArray> basicVao = nullptr;
		
		static void InitBasicGraphics()
		{			
			basicShader = Shader::Create("Renderer simple 2D", shaderVersion + vertexShader, shaderVersion + fragmentShader, false);
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

		#define CHECK_INIT if(Renderer::GetRenderer() == nullptr) { LOG_ERROR("The renderer has not been initialized yet!"); return; } if(!s_isInit) { InitBasicGraphics(); s_isInit = true; }
		
		void Renderer2D::Clear(const glm::vec4& color)
		{
			CHECK_INIT

			Renderer::GetRenderer()->clearColor(color);
			Renderer::GetRenderer()->clearBuffers();
		}

		void Renderer2D::SetColor(const glm::vec4& color)
		{
			CHECK_INIT

			basicShader->bind();
			basicShader->loadVector4("color", color);
		}

		void Renderer2D::DrawRectangle(const glm::vec2& position, float rotation, const glm::vec2& scale)
		{
			CHECK_INIT

			const glm::mat4 modelMatrix = Utils::Math::CreateModelMatrix({ position.x, position.y, -1 }, { 0, 0, rotation }, { scale.x, scale.y, 1 });

			auto& window = App::Application::GetInstance().getWindow();
			float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);

			basicShader->bind();
			basicShader->loadInt("useTex", false);
			basicShader->loadMatrix4("_modelMatrix", modelMatrix);
			basicShader->loadMatrix4("_projectionMatrix", glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, 0.1f, 1.1f));

			basicVao->bind();
			Renderer::GetRenderer()->draw(basicVao);
		}

		void Renderer2D::DrawImage(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture)
		{
			CHECK_INIT

			const glm::mat4 modelMatrix = Utils::Math::CreateModelMatrix({ position.x, position.y, -1 }, { 0, 0, rotation }, { scale.x, scale.y, 1 });

			auto& window = App::Application::GetInstance().getWindow();
			float aspect = (window.getWidth() * 1.0f) / (window.getHeight() * 1.0f);

			basicShader->bind();
			basicShader->loadInt("useTex", true);
			basicShader->loadMatrix4("_modelMatrix", modelMatrix);
			basicShader->loadMatrix4("_projectionMatrix", glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, 0.1f, 1.1f));

			texture->bind(0);

			basicVao->bind();
			Renderer::GetRenderer()->draw(basicVao);
		}
	}
}
