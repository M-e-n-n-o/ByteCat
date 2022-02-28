#pragma once
#include <ByteCat.h>

#include "CameraBehaviour.h"
#include "glm/gtc/matrix_access.hpp"

using namespace BC;

class TestLayer : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;

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

		// Cube data
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

			auto standardShader = Shader::Create("Standard", "StandardVertex.glsl", "StandardFragment.glsl");
			standardShader->setTextureSlots({ "tex" });


		// Framebuffer + cloud spul
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
			quadShader->setTextureSlots({ "cloudNoise", "screenTexture", "depthTexture" });
			quadShader->loadFloat("numSteps", 50);
			quadShader->loadFloat("numStepsLight", 15);
		
			auto cloudTexture = Texture3D::Create(128, 128, 128, TextureFormat::RGBA8);

			auto computeShader = ComputeShader::Create("Test Compute", "TestCompute.glsl");
			computeShader->setOutputTexture(cloudTexture);
			computeShader->compute(cloudTexture->getWidth(), cloudTexture->getHeight(), 64);
			computeShader->wait();
		
			renderable = { CullingMode::Back, quad, quadShader, {cloudTexture, colorAttachment, depthAttachment}, Math::CreateModelMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)) };

		
		// Entities + components aanmaken
			auto texture = Texture2D::Create("wall.jpg");

			auto entity = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
			ecsCoordinator->addComponent<Mesh>(entity, { vao });
			ecsCoordinator->addComponent<Material>(entity, { CullingMode::Back, standardShader, {texture} });

			auto entity2 = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(entity2, { glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
			ecsCoordinator->addComponent<Mesh>(entity2, { vao });
			ecsCoordinator->addComponent<Material>(entity2, { CullingMode::Back, standardShader, {texture} });
		
			camera = ecsCoordinator->createEntity("Camera");
			ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 20, -10), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
			ecsCoordinator->addComponent<Camera>(camera, { 70, 0.1f, 1000.0f });
			ecsCoordinator->setBehaviour<CameraBehaviour>(camera);
	}

	void onUpdate() override
	{
		static float x = 0;
		x += Time::GetDeltaTime() / 2;
		
		quadShader->loadVector3("cloudOffset", glm::vec3(x, 0, 0));
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

	inline static bool captured = false;

	void onGuiRender() override
	{
		if (captured)
		{
			ImGui::Begin("Settings");
			
			ImGui::Text("Cloud Settings");
			{
				static float cloudScale = 10;
				ImGui::DragFloat("Scale", &cloudScale, 0.1);
				quadShader->loadFloat("cloudScale", cloudScale);

				static float minPos[3] = { -20, -5, -20 };
				ImGui::DragFloat3("Min position", minPos, 0.1);
				quadShader->loadVector3("boxMin", glm::vec3(minPos[0], minPos[1], minPos[2]));

				static float maxPos[3] = { 50, 10, 50 };
				ImGui::DragFloat3("Max position", maxPos, 0.1);
				quadShader->loadVector3("boxMax", glm::vec3(maxPos[0], maxPos[1], maxPos[2]));
				
				static float densityThreshold = 0.52;
				ImGui::SliderFloat("Density threshold", &densityThreshold, 0, 1);
				quadShader->loadFloat("densityThreshold", densityThreshold);

				static float densityMultiplier = 1.3;
				ImGui::DragFloat("Density multiplier", &densityMultiplier, 0.01);
				quadShader->loadFloat("densityMultiplier", densityMultiplier);
			}

			ImGui::Text("Light Settings");
			{
				static float sunPos[3] = { 0, 10, 0 };
				ImGui::DragFloat3("Sun position", sunPos);				
				quadShader->loadVector3("lightPos", glm::vec3(sunPos[0], sunPos[1], sunPos[2]));

				static float sunCol[3] = { 1, 0.5, 0.14 };
				ImGui::SliderFloat3("Sun color", sunCol, 0, 1);
				quadShader->loadVector3("lightColor", glm::vec3(sunCol[0], sunCol[1], sunCol[2]));

				static float lightAbsorptionThroughCloud = 0.95;
				ImGui::DragFloat("Light absorption through cloud", &lightAbsorptionThroughCloud, 0.01);
				quadShader->loadFloat("lightAbsorptionThroughCloud", lightAbsorptionThroughCloud);

				static float lightAbsorptionTowardSun = 1.25;
				ImGui::DragFloat("Light absorption towards sun", &lightAbsorptionTowardSun, 0.01);
				quadShader->loadFloat("lightAbsorptionTowardSun", lightAbsorptionTowardSun);

				static float darknessThreshold = 0;
				ImGui::SliderFloat("Darkness Threshold", &darknessThreshold, 0, 1);
				quadShader->loadFloat("darknessThreshold", darknessThreshold);
			}
			
			ImGui::End();
		}
	}

	void onEvent(Event& event) override
	{
		if (KeyPressedEvent* keyEvent = dynamic_cast<KeyPressedEvent*>(&event); keyEvent != nullptr)
		{
			if (keyEvent->getKeyCode() == KeyCode::Escape)
			{
				Application::GetInstance().getWindow().captureMouse(captured);
				ecsCoordinator->enableBehaviour<CameraBehaviour>(camera, captured);
				captured = !captured;
				
				Input::GetMouseVelocity();
			}
		}
	}
};