#include <ByteCat.h>

using namespace BC;

class TestSystem : public System
{
public:
	void onUpdate(EcsCoordinator& coordinator) override
	{
		LOG_INFO("TestSystem update");
	}
};

class TestBehaviour : public Behaviour
{
public:	
	void onAttach() override
	{
		LOG_INFO("TestBehaviour onAttach");
	}
	
	void onUpdate(EcsCoordinator& coordinator) override
	{
		LOG_INFO("TestBehaviour onUpdate, entity number: {0}", m_entity);
	}
	
	void onDetach() override
	{
		LOG_INFO("TestBehaviour onDettach");
	}
};


class ExampleLayer : public Layer
{
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<VertexArray> vao;

	SceneManager sceneManager;
public:
	ExampleLayer() : Layer("ExampleLayer")
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
		auto scene = sceneManager.CreateScene("TestScene");

		auto ecsCoordinator = scene->getEcsCoordinator();

		ecsCoordinator->registerComponent<Transform>();
		
		// Maak en configureer een system
		auto system = ecsCoordinator->registerSystem<TestSystem>();
		// Signature signature;
		// signature.set(coordinator.getComponentType<Behaviour>());
		// coordinator.setSystemSignature<BehaviourSystem>(signature);
		
		// Maak een entity en voeg components toe
		auto entity = ecsCoordinator->createEntity();
		ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0) });
		ecsCoordinator->setBehaviour<TestBehaviour>(entity);
	}

	void onUpdate() override
	{
		sceneManager.GetScene("TestScene")->update();
	}

	void onRender() override
	{
		Renderer::Submit({ vao, shader });
	}

	~ExampleLayer()
	{

	}
};


class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox()
	{
		pushLayer(new ExampleLayer());
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