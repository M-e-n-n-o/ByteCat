#pragma once
#include <ByteCat.h>

#include "CameraBehaviour.h"
#include "glm/gtc/matrix_access.hpp"

using namespace BC;

class TestLayer : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;
	Entity entity;

	std::shared_ptr<ComputeShader> computeShader;
	std::shared_ptr<Texture3D> computeTexture;

	Entity camera;
	
	std::shared_ptr<FrameBuffer> fbo;
	std::shared_ptr<Shader> quadShader;
	Renderable renderable;

public:
	TestLayer() : Layer("UserLayer")
	{		
		// Maak een nieuwe scene
			auto scene = SceneManager::CreateScene("TestScene");
			scene->registerDefaultSystems();
			SceneManager::ActivateScene(scene);

			ecsCoordinator = scene->getEcsCoordinator();

		
		// Maak een shader
			auto cloudShader = Shader::Create("Cloud shader", "VolumetricRayMarchVertex.glsl", "VolumetricRayMarchFragment.glsl");
			cloudShader->setTextureSlots({ "noiseTexture" });
			cloudShader->loadVector3("sunPos", glm::vec3(0, 100, 0));

			auto standardShader = Shader::Create("Standard", "StandardVertex.glsl", "StandardFragment.glsl");
			standardShader->setTextureSlots({ "tex" });

		// Maak een vao met data
			float data[] =
			{
				// Vertex pos		Texture coords
				0.5, -0.5, 0.5,		0, 0,
				-0.5, -0.5, 0.5,    1, 0,
				0.5, 0.5, 0.5,		0, 1,

				-0.5, 0.5, 0.5,		1, 1,
				0.5, 0.5, -0.5,		0, 1,
				-0.5, 0.5, -0.5,	1, 1,

				0.5, -0.5, -0.5,	0, 1,
				-0.5, -0.5, -0.5,	1, 1,
				0.5, 0.5, 0.5,		0, 0,

				-0.5, 0.5, 0.5,		1, 0,
				0.5, 0.5, -0.5,		0, 0,
				-0.5, 0.5, -0.5,	1, 0,

				0.5, -0.5, -0.5,	0, 0,
				0.5, -0.5, 0.5,		0, 1,
				-0.5, -0.5, 0.5,	1, 1,

				-0.5, -0.5, -0.5,	1, 0,
				-0.5, -0.5, 0.5,	0, 0,
				-0.5, 0.5, 0.5,		0, 1,

				-0.5, 0.5, -0.5,	1, 1,
				-0.5, -0.5, -0.5,	1, 0,
				0.5, -0.5, -0.5,	0, 0,

				0.5, 0.5, -0.5,		0, 1,
				0.5, 0.5, 0.5,		1, 1,
				0.5, -0.5, 0.5,		1, 0
			};

			unsigned indices[] =
			{
				0, 2, 3,
				0, 3, 1,
				
				8, 4, 5,
				8, 5, 9,
				
				10, 6, 7,
				10, 7, 11,
				
				12, 13, 14,
				12, 14, 15,
				
				16, 17, 18,
				16, 18, 19,
				
				20, 21, 22,
				20, 22, 23
			};
			
			auto vao = VertexArray::Create();
		
			auto vbo = VertexBuffer::Create(data, sizeof(data));
			BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" }, {ShaderDataType::Float2, "texCoord"} };
			vbo->setLayout(layout);
			vao->addVertexBuffer(vbo);

			auto ebo = IndexBuffer::Create(indices, sizeof(indices));
			vao->setIndexBuffer(ebo);


		// Framebuffer spul
			 auto& window = Application::GetInstance().getWindow();
			 fbo = FrameBuffer::Create("Test", window.getWidth(), window.getHeight());
			 auto colorAttachment = Texture2D::Create(window.getWidth(), window.getHeight(), TextureFormat::RGB16F);
			 auto depthAttachment = Texture2D::Create(window.getWidth(), window.getHeight(), TextureFormat::DEPTH);
			 fbo->attachTexture(colorAttachment);
			 fbo->attachTexture(depthAttachment);
			 //fbo->attachRenderBuffer(TextureFormat::DEPTH);
			
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
			
			auto quad = VertexArray::Create();
			auto quadVertexBuffer = VertexBuffer::Create(dataQuad, sizeof(dataQuad));
			quadVertexBuffer->setLayout({ {ShaderDataType::Float2, "vertexPos"}, {ShaderDataType::Float2, "texCoord"} });
			quad->addVertexBuffer(quadVertexBuffer);
			auto quadIndexBuffer = IndexBuffer::Create(indicesQuad, sizeof(indicesQuad));
			quad->setIndexBuffer(quadIndexBuffer);
		
			quadShader = Shader::Create("Quad", "QuadVertex.glsl", "QuadFragment.glsl");
			quadShader->setTextureSlots({ "screenTexture", "depthTexture" });
			quadShader->loadVector3("boxPos", glm::vec3(3, 0, 0));
			quadShader->loadVector3("boxScale", glm::vec3(1, 1, 2));
			quadShader->loadVector3("cloudOffset", glm::vec3(0, 0 ,0));
			quadShader->loadFloat("cloudScale", 1);
			quadShader->loadFloat("densityThreshold", 1);
			quadShader->loadFloat("densityMultiplier", 1);
		
			renderable = { CullingMode::Back, quad, quadShader, {colorAttachment, depthAttachment}, Math::CreateModelMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)) };

		
		// Maak een entity en voeg components toe
			auto texture = Texture2D::Create("wall.jpg");

			//computeTexture = Texture3D::Create(128, 128, 128, TextureFormat::RGBA16F);

			//computeShader = ComputeShader::Create("Test Compute", "TestCompute.glsl");
			//computeShader->setOutputTexture(computeTexture);
			//computeShader->compute(computeTexture->getWidth(), computeTexture->getHeight(), 64);
			//computeShader->wait();
		
			//entity = ecsCoordinator->createEntity("Cloud Entity");
			//ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(5, 5, 5) });
			//ecsCoordinator->addComponent<Mesh>(entity, { vao });
			//ecsCoordinator->addComponent<Material>(entity, { CullingMode::None, RenderLayer::Transparent, cloudShader, {computeTexture} });

			entity = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
			ecsCoordinator->addComponent<Mesh>(entity, { vao });
			ecsCoordinator->addComponent<Material>(entity, { CullingMode::Back, standardShader, {texture} });

			entity = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
			ecsCoordinator->addComponent<Mesh>(entity, { vao });
			ecsCoordinator->addComponent<Material>(entity, { CullingMode::Back, standardShader, {texture} });
		
			camera = ecsCoordinator->createEntity("Camera");
			ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
			ecsCoordinator->addComponent<Camera>(camera, { 70, 0.1f, 1000.0f });
			ecsCoordinator->setBehaviour<CameraBehaviour>(camera);
	}

	void onUpdate() override
	{
		if (Input::IsKeyPressed(KeyCode::R))
		{
			ecsCoordinator->getComponent<Transform>(entity).scale.y += Time::GetDeltaTime();
		}

		if (Input::IsKeyPressed(KeyCode::T))
		{
			ecsCoordinator->getComponent<Transform>(entity).scale.y -= Time::GetDeltaTime();
		}
	}

	void onRender() override
	{
		Renderer::RenderFrame();
		fbo->unbind();
		
		Renderer::Submit(renderable);
	}

	void onRenderComplete() override
	{
		fbo->bind();
	}

	void onEvent(Event& event) override
	{
		if (KeyPressedEvent* keyEvent = dynamic_cast<KeyPressedEvent*>(&event); keyEvent != nullptr)
		{
			if (keyEvent->getKeyCode() == KeyCode::Escape)
			{
				static bool captured = true;
				Application::GetInstance().getWindow().captureMouse(captured);
				captured = !captured;

				Input::GetMouseVelocity();
			}
		}
	}
};