#pragma once
#include <ByteCat.h>

#include "Spectator.h"

using namespace BC;
using namespace Ecs;
using namespace Graphics;
using namespace Utils;
using namespace Inputs;

class LightingTest : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;

	Entity camera;
	Entity skyboxEntity;
	Entity sun;

	std::shared_ptr<Shader> cubeShader;

public:
	LightingTest() : Layer("Shadow Test")
	{
		// Submit de render passes
		Renderer::Submit(std::make_shared<ShadowPass>());
		Renderer::Submit(std::make_shared<ForwardPass>());

		// Maak een nieuwe scene
		Application::GetInstance().pushLayer(new SceneManager);

		auto scene = SceneManager::CreateScene("Shadow Test Scene");
		SceneManager::ActivateScene(scene);

		ecsCoordinator = scene->getEcsCoordinator();
		ecsCoordinator->registerSystem<RenderSubmitter>();
		ecsCoordinator->registerSystem<LightSystem>();
		ecsCoordinator->registerSystem<CameraSystem>();
		ecsCoordinator->registerSystem<SpectatorSystem>();

		// Cube data
		float dataCube[] =
		{
			// Vertex pos		Uv's 		Normals
			0.5, -0.5, 0.5,		0, 0,		0.0, 0.0, 1.0,
			-0.5, -0.5, 0.5,    1, 0,		0.0, 0.0, 1.0,
			0.5, 0.5, 0.5,		0, 1,		0.0, 0.0, 1.0,

			-0.5, 0.5, 0.5,		1, 1,		0.0, 0.0, 1.0,
			0.5, 0.5, -0.5,		0, 1,		0.0, 1.0, 0.0,
			-0.5, 0.5, -0.5,	1, 1,		0.0, 1.0, 0.0,

			0.5, -0.5, -0.5,	0, 1,		0.0, 0.0, -1.0,
			-0.5, -0.5, -0.5,	1, 1,		0.0, 0.0, -1.0,
			0.5, 0.5, 0.5,		0, 0,		0.0, 1.0, 0.0,

			-0.5, 0.5, 0.5,		1, 0,		0.0, 1.0, 0.0,
			0.5, 0.5, -0.5,		0, 0,		0.0, 0.0, -1.0,
			-0.5, 0.5, -0.5,	1, 0,		0.0, 0.0, -1.0,

			0.5, -0.5, -0.5,	0, 0,		0.0, -1.0, 0.0,
			0.5, -0.5, 0.5,		0, 1,		0.0, -1.0, 0.0,
			-0.5, -0.5, 0.5,	1, 1,		0.0, -1.0, 0.0,

			-0.5, -0.5, -0.5,	1, 0,		0.0, -1.0, 0.0,
			-0.5, -0.5, 0.5,	0, 0,		-1.0, 0.0, 0.0,
			-0.5, 0.5, 0.5,		0, 1,		-1.0, 0.0, 0.0,

			-0.5, 0.5, -0.5,	1, 1,		-1.0, 0.0, 0.0,
			-0.5, -0.5, -0.5,	1, 0,		-1.0, 0.0, 0.0,
			0.5, -0.5, -0.5,	0, 0,		1.0, 0.0, 0.0,

			0.5, 0.5, -0.5,		0, 1,		1.0, 0.0, 0.0,
			0.5, 0.5, 0.5,		1, 1,		1.0, 0.0, 0.0,
			0.5, -0.5, 0.5,		1, 0,		1.0, 0.0, 0.0
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
		BufferLayout layoutCube = { { ShaderDataType::Float3, "vertexPos" }, {ShaderDataType::Float2, "texCoord"}, {ShaderDataType::Float3, "normals" } };
		cubeVbo->setLayout(layoutCube);
		cubeVao->addVertexBuffer(cubeVbo);
		auto cubeEbo = IndexBuffer::Create(indicesCube, sizeof(indicesCube));
		cubeVao->setIndexBuffer(cubeEbo);

		auto woodTexture = Texture2D::Create("wood.jpg");
		cubeShader = Shader::Create("Cube shader", "StandardVertex.glsl", "StandardFragment.glsl", true);
		cubeShader->addTexture("mainTexture", woodTexture);

		// Skybox cubemap

		auto skyboxTexture = TextureCube::Create({ "skybox/right.jpg", "skybox/left.jpg", "skybox/top.jpg", "skybox/bottom.jpg", "skybox/front.jpg", "skybox/back.jpg" });

		auto skyboxShader = Shader::Create("SkyboxShader", "skybox/SkyboxVertex.glsl", "skybox/SkyboxFragment.glsl", true);
		skyboxShader->addTexture("skybox", skyboxTexture);

		// Entities + components aanmaken
		skyboxEntity = ecsCoordinator->createEntity("Skybox");
		ecsCoordinator->addComponent<Transform>(skyboxEntity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1000, 1000, 1000) });
		ecsCoordinator->addComponent<Mesh>(skyboxEntity, { cubeVao });
		ecsCoordinator->addComponent<Material>(skyboxEntity, { CullingMode::Front, skyboxShader });

		sun = ecsCoordinator->createEntity("Sun");
		ecsCoordinator->addComponent<Transform>(sun, { glm::vec3(0, 10, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
		ecsCoordinator->addComponent<DirectionalLight>(sun, { glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1, 1, 1) });

		auto cube = ecsCoordinator->createEntity("Cube");
		ecsCoordinator->addComponent<Transform>(cube, { glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
		ecsCoordinator->addComponent<Mesh>(cube, { cubeVao });
		ecsCoordinator->addComponent<Material>(cube, { CullingMode::Back, cubeShader });

		auto cube2 = ecsCoordinator->createEntity("Cube2");
		ecsCoordinator->addComponent<Transform>(cube2, { glm::vec3(2, 2, 0), glm::vec3(45, 45, 0), glm::vec3(2, 0.2f, 3) });
		ecsCoordinator->addComponent<Mesh>(cube2, { cubeVao });
		ecsCoordinator->addComponent<Material>(cube2, { CullingMode::Back, cubeShader });

		auto ground = ecsCoordinator->createEntity("Ground");
		ecsCoordinator->addComponent<Transform>(ground, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(10, 1, 10) });
		ecsCoordinator->addComponent<Mesh>(ground, { cubeVao });
		ecsCoordinator->addComponent<Material>(ground, { CullingMode::Back, cubeShader });

		camera = ecsCoordinator->createEntity("Camera");
		ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 5, -5), glm::vec3(0, 90, 0), glm::vec3(1, 1, 1) });
		//ecsCoordinator->addComponent<OrtographicCamera>(camera, { -10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f });
		ecsCoordinator->addComponent<PerspectiveCamera>(camera, { 70, 0.1f, 1000.0f });
		ecsCoordinator->addComponent<Spectator>(camera, { 10 });
	}

	void onUpdate() override
	{
		auto cameraPos = ecsCoordinator->getComponent<Transform>(camera)->position;
		ecsCoordinator->getComponent<Transform>(skyboxEntity)->position = cameraPos;
		ecsCoordinator->getComponent<Transform>(sun)->position = cameraPos;
	}

	void onEvent(Event& event) override
	{
		static float bias = 0.04;

		if (KeyPressedEvent* keyEvent = dynamic_cast<KeyPressedEvent*>(&event); keyEvent != nullptr)
		{
			if (keyEvent->getKeyCode() == KeyCode::Up)
			{
				bias += 0.01;
				cubeShader->loadFloat("biasStandard", bias);
			}

			if (keyEvent->getKeyCode() == KeyCode::Down)
			{
				bias -= 0.01;
				cubeShader->loadFloat("biasStandard", bias);
			}

			LOG_INFO("%f", bias);
		}
	}
};