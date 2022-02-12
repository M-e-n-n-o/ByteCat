#pragma once
#include <ByteCat.h>

#include "glm/ext/matrix_clip_space.hpp"

using namespace BC;

class TestLayer : public Layer
{
	Transform camera;
	
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

			uniform mat4 modelMatrix;
			uniform mat4 viewMatrix;
			uniform mat4 projectionMatrix;
		
			void main()
			{
				gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
			}
		)";

		const char* fragmentSource = R"(
			#version 330 core

			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			}
		)";

		auto shader = Shader::Create("Test", vertexSource, fragmentSource);


		// Maak een vao met data
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2
		};

		auto vao = VertexArray::Create();

		auto ebo = IndexBuffer::Create(indices, sizeof(indices));
		vao->setIndexBuffer(ebo);

		auto vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" } };
		vbo->setLayout(layout);
		vao->addVertexBuffer(vbo);
		

		// Maak een entity en voeg components toe
		auto entity = ecsCoordinator->createEntity("Test Entity");
		ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
		ecsCoordinator->addComponent<Mesh>(entity, { vao });
		ecsCoordinator->addComponent<Material>(entity, { shader });

		camera = Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	}

	void onUpdate() override
	{		
		if (Input::IsKeyPressed(KeyCode::W))
		{
			camera.position.z -= 0.01f;
		}

		if (Input::IsKeyPressed(KeyCode::S))
		{
			camera.position.z += 0.01f;
		}

		if (Input::IsKeyPressed(KeyCode::D))
		{
			camera.position.x += 0.01f;
		}

		if (Input::IsKeyPressed(KeyCode::A))
		{
			camera.position.x -= 0.01f;
		}
		
		Renderer::SetSceneData({
				Math::CreateViewMatrix(camera.position, glm::vec3(0, 0, 0)),
				glm::perspective(glm::radians(70.0f), (1280 * 1.0f) / (720 * 1.0f), 0.01f, 1000.0f) });
	}

	void onRender() override
	{
		
	}

	~TestLayer()
	{

	}
};