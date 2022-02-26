#pragma once
#include <ByteCat.h>

#include "CameraBehaviour.h"

using namespace BC;

class TestLayer : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;
	Entity entity;

	std::shared_ptr<ComputeShader> computeShader;
	std::shared_ptr<Texture2D> computeTexture;
	
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
		
			//std::vector<glm::vec3> points;
			//for (int i = 0; i < 20; i++)
			//{
			//	points.push_back(glm::vec3( Math::RandomBetween(0, 0.4), Math::RandomBetween(0, 0.4), Math::RandomBetween(0, 0.4) ));
			//}
			//cloudShader->loadVector3Array("points", points);

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

			auto ebo = IndexBuffer::Create(indices, sizeof(indices));
			vao->setIndexBuffer(ebo);
		
			auto vbo = VertexBuffer::Create(data, sizeof(data));
			BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" }, {ShaderDataType::Float2, "texCoord"} };
			vbo->setLayout(layout);
			vao->addVertexBuffer(vbo);
		

		// Maak een entity en voeg components toe
			//auto texture = Texture2D::Create("wall.jpg", 0.5);
			auto noiseTexture = Texture2D::Create("volumeWisp.tga", 0.5);

			//entity = ecsCoordinator->createEntity("Cloud Entity");
			//ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(20, 20, 20) });
			//ecsCoordinator->addComponent<Mesh>(entity, { vao });
			//ecsCoordinator->addComponent<Material>(entity, { CullingMode::None, RenderLayer::Transparent, cloudShader, {noiseTexture} });

			// entity = ecsCoordinator->createEntity("Test Entity");
			// ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
			// ecsCoordinator->addComponent<Mesh>(entity, { vao });
			// ecsCoordinator->addComponent<Material>(entity, { CullingMode::Back, RenderLayer::Opaque, standardShader });
		
			auto camera = ecsCoordinator->createEntity("Camera");
			ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
			ecsCoordinator->addComponent<Camera>(camera, { 70, 0.01f, 1000.0f });
			ecsCoordinator->setBehaviour<CameraBehaviour>(camera);



		
		computeTexture = Texture2D::Create(512, 512, TextureFormat::RGBA);
		
		computeShader = ComputeShader::Create("Test Compute", "TestCompute.glsl");
		computeShader->setOutputTexture(computeTexture);

		computeShader->compute(computeTexture->getWidth(), computeTexture->getHeight(), 1);
		computeShader->wait();

		entity = ecsCoordinator->createEntity("Test Entity");
		ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
		ecsCoordinator->addComponent<Mesh>(entity, { vao });
		ecsCoordinator->addComponent<Material>(entity, { CullingMode::Back, RenderLayer::Opaque, standardShader, {computeTexture} });
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