#pragma once
#include <ByteCat.h>

#include "CameraBehaviour.h"

using namespace BC;

class TestLayer : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;
	Entity entity;
	
public:
	TestLayer() : Layer("UserLayer")
	{
		RendererAPI::SetCullingMode(CullingMode::None);
		
		// Maak een nieuwe scene
			auto scene = SceneManager::CreateScene("TestScene");
			scene->registerDefaultSystems();
			SceneManager::ActivateScene(scene);

			ecsCoordinator = scene->getEcsCoordinator();

		
		// Maak een shader
			#pragma region
			const char* vertexSource = R"(
				#version 330 core

				layout (location = 0) in vec3 vertexPos;
				layout (location = 1) in vec2 texCoord;

				out v2f
				{
					vec2 uv;
					vec3 originPos;
					vec3 hitPos;
				} output;

				uniform mat4 modelMatrix;
				uniform mat4 viewMatrix;
				uniform mat4 projectionMatrix;
					
				uniform vec3 cameraPos;

				void main()
				{		
					output.uv = texCoord;
					output.originPos = cameraPos;		
					output.hitPos = (modelMatrix * vec4(vertexPos, 1.0)).xyz;
					
					gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
				}
			)";
			#pragma endregion VertexShader

			#pragma region
			const char* fragmentSource = R"(
				#version 330 core

				#define MAX_STEPS 100
				#define MIN_DISTANCE 0.001
				#define MAX_DISTANCE 100
					
				in v2f
				{
					vec2 uv;
					vec3 originPos;
					vec3 hitPos;	
				} input;

				out vec4 FragColor;

				uniform sampler2D texture1;
		

				float getDistance(vec3 point)
				{
					//float distance = length(point) - 0.5;
					float distance = length(vec2(length(point.xz) - 0.5, point.y)) - 0.1;
					return distance;
				}

					
				float rayMarch(vec3 rayOrigin, vec3 rayDirection)
				{
					float distanceOrigin = 0;
					float distanceSurface = 0;

					for (int i = 0; i < MAX_STEPS; i++)
					{
						vec3 point = rayOrigin + distanceOrigin * rayDirection;
						distanceSurface = getDistance(point);
						distanceOrigin += distanceSurface;

						if (distanceSurface < MIN_DISTANCE || distanceOrigin > MAX_DISTANCE)
						{
							break;
						}
					}

					return distanceOrigin;
				}

				vec3 getNormal(vec3 point)
				{
					vec2 epsilon = vec2(0.01, 0);
					
					vec3 normal = getDistance(point) - vec3(
						getDistance(point - epsilon.xyy),
						getDistance(point - epsilon.yxy),
						getDistance(point - epsilon.yyx)
						);

					return normalize(normal);
				}
					
				void main()
				{
					vec2 uv = input.uv - 0.5;
					vec3 rayOrigin = input.originPos;
					vec3 rayDirection = normalize(input.hitPos - rayOrigin);

					float distance = rayMarch(rayOrigin, rayDirection);
					
					vec4 col = vec4(0, 0, 0, 1);

					if (distance < MAX_DISTANCE)
					{		
						vec3 point = rayOrigin + rayDirection * distance;
						vec3 normal = getNormal(point);
						col.rgb = normal;
					} else
					{
						discard;
					}

					FragColor = col;
				}
			)";
			#pragma endregion FragmentShader

			auto shader = Shader::Create("Test", vertexSource, fragmentSource);
			shader->setTextureSlots({ "texture1" });


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
			auto texture = Texture2D::Create("wall.jpg", 0.5);

			entity = ecsCoordinator->createEntity("Test Entity");
			ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(5, 5, 5) });
			ecsCoordinator->addComponent<Mesh>(entity, { vao });
			ecsCoordinator->addComponent<Material>(entity, { shader, { texture } });

			auto camera = ecsCoordinator->createEntity("Camera");
			ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
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
};