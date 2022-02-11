#include <ByteCat.h>

using namespace BC;


struct TestComponent
{
	int x;
};

class TestSystem : public System
{
public:
	void onUpdate() override
	{
		for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++)
		{
			LOG_INFO("TestSystem update, {0}", m_coordinator->getComponent<TestComponent>(*itr).x);
		}
	}
};

class TestBehaviour : public Behaviour
{
public:	
	void onAttach() override
	{
		LOG_INFO("TestBehaviour onAttach");
	}
	
	void onUpdate() override
	{
		LOG_INFO("TestBehaviour onUpdate, entity number: {0}", m_entity);
	}
	
	void onDetach() override
	{
		LOG_INFO("TestBehaviour onDettach");
	}
};


class UserLayer : public Layer
{
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<VertexArray> vao;

public:
	UserLayer() : Layer("UserLayer")
	{
		const char* vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 vertexPos;
		
			void main()
			{
				gl_Position = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0);
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

		shader = Shader::Create("Test", vertexSource, fragmentSource);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2
		};

		vao = VertexArray::Create();

		auto ebo = IndexBuffer::Create(indices, sizeof(indices));
		vao->setIndexBuffer(ebo);

		auto vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" } };
		vbo->setLayout(layout);
		vao->addVertexBuffer(vbo);


		

		
		// Registreer de components
		auto scene = SceneManager::CreateScene("TestScene");
		SceneManager::ActivateScene(scene);

		auto ecsCoordinator = scene->getEcsCoordinator();

		ecsCoordinator->registerComponent<Transform>();
		ecsCoordinator->registerComponent<TestComponent>();
		
		// Maak en configureer een system
		auto system = ecsCoordinator->registerSystem<TestSystem>();
		Signature signature;
		signature.set(ecsCoordinator->getComponentType<TestComponent>());
		ecsCoordinator->setSystemSignature<TestSystem>(signature);
		
		// Maak een entity en voeg components toe
		auto entity = ecsCoordinator->createEntity();
		ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(69, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0) });
		ecsCoordinator->addComponent<TestComponent>(entity, {5});
		ecsCoordinator->setBehaviour<TestBehaviour>(entity);
	}

	void onUpdate() override
	{

	}

	void onRender() override
	{
		Renderer::Submit({ vao, shader });
	}

	~UserLayer()
	{

	}
};


class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox()
	{
		pushLayer(new UserLayer());
	}

	// The end of your application
	~Sandbox() override
	{

	}
};

Application* BC::CreateApplication()
{
	return new Sandbox();
}