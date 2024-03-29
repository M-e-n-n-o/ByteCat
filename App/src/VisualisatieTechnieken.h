#pragma once
#include <memory>
#include <ByteCat.h>

#include "Spectator.h"

using namespace BC;
using namespace Ecs;
using namespace Graphics;
using namespace Utils;
using namespace Inputs;

class VisualisatieTechnieken : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;

	std::shared_ptr<Shader> rayMarchShader;
	
	Entity camera;
	Entity skyboxEntity;
	
	std::shared_ptr<FrameBuffer> fbo;
	std::shared_ptr<Shader> cloudShader;
	std::shared_ptr<Renderable> renderable;

public:
	VisualisatieTechnieken() : Layer("Visualisatie Technieken")
	{
		// Zet een submission renderer
			Renderer::Submit(std::make_shared<ForwardPass>());
		
		// Maak een nieuwe scene
			Application::GetInstance().pushLayer(new SceneManager);
		
			auto scene = SceneManager::CreateScene("TestScene");
			SceneManager::ActivateScene(scene);
		
			ecsCoordinator = scene->getEcsCoordinator();
			ecsCoordinator->registerSystem<RenderSubmitter>();
			ecsCoordinator->registerSystem<CameraSystem>();
			ecsCoordinator->registerSystem<SpectatorSystem>();
			
		// Cube data
			float dataCube[] =
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
		
			unsigned indicesCube[] =
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
			
			auto cubeVao = VertexArray::Create();
		
			auto cubeVbo = VertexBuffer::Create(dataCube, sizeof(dataCube));
			BufferLayout layoutCube = { { ShaderDataType::Float3, "vertexPos" }, {ShaderDataType::Float2, "texCoord"} };
			cubeVbo->setLayout(layoutCube);
			cubeVao->addVertexBuffer(cubeVbo);
		
			auto cubeEbo = IndexBuffer::Create(indicesCube, sizeof(indicesCube));
			cubeVao->setIndexBuffer(cubeEbo);
		
			rayMarchShader = Shader::Create("RayMarch", "RayMarchVertex.glsl", "RayMarchFragment.glsl", true);

			auto rgbNoise = Texture2D::Create("rgbNoise.png");
			auto windNoise = Texture2D::Create("windNoise.png");

			auto grassShader = Shader::Create("Grass", "GrassVertex.glsl", "GrassGeometry.glsl", "GrassFragment.glsl", true);
			grassShader->addTexture("noise", rgbNoise);
			grassShader->addTexture("windNoise", windNoise);
		
		// Framebuffer + cloud spul
			 auto& window = Application::GetInstance().getWindow();
			 fbo = FrameBuffer::Create("Test", window.getWidth(), window.getHeight());
			 auto colorAttachment = Texture2D::Create(window.getWidth(), window.getHeight(), TextureFormat::RGB8);
			 auto depthAttachment = Texture2D::Create(window.getWidth(), window.getHeight(), TextureFormat::DEPTH16);
			 fbo->attachTexture(colorAttachment);
			 fbo->attachTexture(depthAttachment);
			
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
		
			auto cloudTexture = Texture3D::Create(128, 128, 128, TextureFormat::RGBA8);

			auto computeShader = ComputeShader::Create("Cloud Noise Compute", "CloudNoiseCompute.glsl");
			computeShader->setOutputTexture(cloudTexture);
			computeShader->compute(cloudTexture->getWidth(), cloudTexture->getHeight(), 64);
			computeShader->waitToFinish();

			cloudShader = Shader::Create("Cloud shader", "CloudVertex.glsl", "CloudFragment.glsl", true);
			cloudShader->addTexture("cloudNoise", cloudTexture);
			cloudShader->addTexture("screenTexture", colorAttachment);
			cloudShader->addTexture("depthTexture", depthAttachment);
			cloudShader->loadFloat("numSteps", 20);
			cloudShader->loadFloat("numStepsLight", 10);
		
			renderable = std::make_shared<Renderable>(CullingMode::Back, quad, cloudShader, Math::CreateModelMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
		
		// Skybox cubemap
			auto skyboxTexture = TextureCube::Create({ "skybox/right.jpg", "skybox/left.jpg", "skybox/top.jpg", "skybox/bottom.jpg", "skybox/front.jpg", "skybox/back.jpg" });
		
			auto skyboxShader = Shader::Create("SkyboxShader", "skybox/SkyboxVertex.glsl", "skybox/SkyboxFragment.glsl", true);
			skyboxShader->addTexture("skybox", skyboxTexture);
		
		
		// Entities + components aanmaken		
			auto mandelbrot = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(mandelbrot, { glm::vec3(0, 50, 0), glm::vec3(0, 0, 0), glm::vec3(5, 5, 5) });
			ecsCoordinator->addComponent<Mesh>(mandelbrot, { cubeVao });
			ecsCoordinator->addComponent<Material>(mandelbrot, { CullingMode::None, rayMarchShader });
		
			auto grass = ecsCoordinator->createEntity("Test Entity2");
			ecsCoordinator->addComponent<Transform>(grass, { glm::vec3(0, 40, 0), glm::vec3(-90, 0, 0), glm::vec3(5, 5, 5) });
			ecsCoordinator->addComponent<Mesh>(grass, { quad });
			ecsCoordinator->addComponent<Material>(grass, { CullingMode::Back, grassShader });
		
			skyboxEntity = ecsCoordinator->createEntity("Skybox Entity");		
			ecsCoordinator->addComponent<Transform>(skyboxEntity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1000, 1000, 1000) });
			ecsCoordinator->addComponent<Mesh>(skyboxEntity, { cubeVao });
			ecsCoordinator->addComponent<Material>(skyboxEntity, { CullingMode::Front, skyboxShader });
		
			camera = ecsCoordinator->createEntity("Camera");		
			ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 50, -5), glm::vec3(0, 90, 0), glm::vec3(1, 1, 1) });
			ecsCoordinator->addComponent<PerspectiveCamera>(camera, { 70, 0.1f, 1000.0f });
			ecsCoordinator->addComponent<Spectator>(camera, { 10 });
	}

	void onUpdate() override
	{
		static float x = 0;
		x += Time::GetDeltaTime() / 1;
		
		cloudShader->bind();
		cloudShader->loadVector3("cloudOffset", glm::vec3(x, 0, 0));
		
		auto cameraPos = ecsCoordinator->getComponent<Transform>(camera)->position;
		ecsCoordinator->getComponent<Transform>(skyboxEntity)->position = cameraPos;
	}
	
	void beforeRender() override
	{
		Renderer::Render();
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
			// ImGui::Begin("Settings");
			//
			// cloudShader->bind();
			// ImGui::Text("Cloud Settings");
			// {
			// 	static float cloudScale = 2.5;
			// 	ImGui::DragFloat("Scale", &cloudScale, 0.1);
			// 	cloudShader->loadFloat("cloudScale", cloudScale);
			//
			// 	static float minPos[3] = { -100, -20, -100 };
			// 	ImGui::DragFloat3("Min position", minPos, 0.1);
			// 	cloudShader->loadVector3("boxMin", glm::vec3(minPos[0], minPos[1], minPos[2]));
			//
			// 	static float maxPos[3] = { 100, 30, 100 };
			// 	ImGui::DragFloat3("Max position", maxPos, 0.1);
			// 	cloudShader->loadVector3("boxMax", glm::vec3(maxPos[0], maxPos[1], maxPos[2]));
			// 	
			// 	static float densityThreshold = 0.52f;
			// 	ImGui::SliderFloat("Density threshold", &densityThreshold, 0, 1);
			// 	cloudShader->loadFloat("densityThreshold", densityThreshold);
			//
			// 	static float densityMultiplier = 0.26f;
			// 	ImGui::DragFloat("Density multiplier", &densityMultiplier, 0.01);
			// 	cloudShader->loadFloat("densityMultiplier", densityMultiplier);
			//
			// 	static float edgeFadeDistance = 30;
			// 	ImGui::DragFloat("Edge fade distance", &edgeFadeDistance, 0.1);
			// 	cloudShader->loadFloat("edgeFadeDistance", edgeFadeDistance);
			// }
			//
			// ImGui::Text("Light Settings");
			// {
			// 	static float sunPos[3] = { 0, 500, 0 };
			// 	ImGui::DragFloat3("Sun position", sunPos);				
			// 	cloudShader->loadVector3("lightPos", glm::vec3(sunPos[0], sunPos[1], sunPos[2]));
			//
			// 	static float sunCol[3] = { 1, 1, 1 };
			// 	ImGui::SliderFloat3("Sun color", sunCol, 0, 1);
			// 	cloudShader->loadVector3("lightColor", glm::vec3(sunCol[0], sunCol[1], sunCol[2]));
			//
			// 	static float lightAbsorptionThroughCloud = 0.37f;
			// 	ImGui::DragFloat("Light absorption through cloud", &lightAbsorptionThroughCloud, 0.01);
			// 	cloudShader->loadFloat("lightAbsorptionThroughCloud", lightAbsorptionThroughCloud);
			//
			// 	static float lightAbsorptionTowardSun = 1.25f;
			// 	ImGui::DragFloat("Light absorption towards sun", &lightAbsorptionTowardSun, 0.01);
			// 	cloudShader->loadFloat("lightAbsorptionTowardSun", lightAbsorptionTowardSun);
			//
			// 	static float darknessThreshold = 0;
			// 	ImGui::SliderFloat("Darkness Threshold", &darknessThreshold, 0, 1);
			// 	cloudShader->loadFloat("darknessThreshold", darknessThreshold);
			// }
			//
			// ImGui::End();
		}
	}
	
	void onEvent(Event& event) override
	{
		if (KeyPressedEvent* keyEvent = dynamic_cast<KeyPressedEvent*>(&event); keyEvent != nullptr)
		{
			if (keyEvent->getKeyCode() == KeyCode::Escape)
			{
				Application::GetInstance().getWindow().captureMouse(captured);
				captured = !captured;
				
				//Input<>::GetMouseVelocity();
			}
		}
	}
};