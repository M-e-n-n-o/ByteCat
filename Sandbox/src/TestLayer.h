#pragma once
#include <ByteCat.h>

#include "CameraBehaviour.h"

using namespace BC;

class TestLayer : public Layer
{	
public:
	TestLayer() : Layer("UserLayer")
	{
		// Maak een nieuwe scene
		auto scene = SceneManager::CreateScene("TestScene");
		scene->registerDefaultSystems();
		SceneManager::ActivateScene(scene);

		auto ecsCoordinator = scene->getEcsCoordinator();

		
		// Maak een shader
		const char* vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 vertexPos;
			layout (location = 1) in vec2 texCoord;

			out vec2 passTexCoord;
		
			uniform mat4 modelMatrix;
			uniform mat4 viewMatrix;
			uniform mat4 projectionMatrix;
		
			void main()
			{
				passTexCoord = texCoord;
				gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
			}
		)";

		const char* fragmentSource = R"(
			#version 330 core

			in vec2 passTexCoord;
		
			out vec4 FragColor;

			uniform sampler2D texture1;
		
			void main()
			{
				vec4 textureColor = texture(texture1, passTexCoord);
				FragColor = textureColor;
			}
		)";

		auto shader = Shader::Create("Test", vertexSource, fragmentSource);


		// Maak een vao met data
		float data[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,		0.5f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2
		};

		auto vao = VertexArray::Create();

		auto ebo = IndexBuffer::Create(indices, sizeof(indices));
		vao->setIndexBuffer(ebo);

		auto vbo = VertexBuffer::Create(data, sizeof(data));
		BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" }, {ShaderDataType::Float2, "texCoord"} };
		vbo->setLayout(layout);
		vao->addVertexBuffer(vbo);

		// Laad een prachtige texture in
		auto texture = Texture2D::Create("dog.png", 1);

		// Maak een entity en voeg components toe
		auto entity = ecsCoordinator->createEntity("Test Entity");
		ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
		ecsCoordinator->addComponent<Mesh>(entity, { vao });
		ecsCoordinator->addComponent<Material>(entity, { shader, {texture}});

		auto camera = ecsCoordinator->createEntity("Camera");
		ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
		ecsCoordinator->setBehaviour<CameraBehaviour>(camera);
	}

	void onUpdate() override
	{

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

	~TestLayer()
	{

	}
};