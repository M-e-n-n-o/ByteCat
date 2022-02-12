#include <ByteCat.h>

using namespace BC;


struct Camera : Component
{	
	int x;

	Camera() = default;
	Camera(int x): x(x) {}

	TYPE_NAME("Camera")
};

struct PerspectiveCamera : Camera
{
	PerspectiveCamera() : Camera(5) {}
};

struct OrthographicCamera : Camera
{
	OrthographicCamera() : Camera(10) {}
};


class TestSystem : public System
{
public:
	void onUpdate() override
	{

	}
};

class TestBehaviour : public Behaviour
{
public:	
	void onAttach() override
	{

	}
	
	void onUpdate() override
	{

	}
	
	void onDetach() override
	{

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


		
		auto scene = SceneManager::CreateScene("TestScene");
		SceneManager::ActivateScene(scene);

		auto ecsCoordinator = scene->getEcsCoordinator();

		// Not needed anymore
		// ecsCoordinator->registerComponent<Transform>();
		// ecsCoordinator->registerComponent<TestComponent>();
		
		// Maak en configureer een system
		auto system = ecsCoordinator->registerSystem<TestSystem>();
		Signature signature;
		signature.set(ecsCoordinator->getComponentType<Camera>());
		ecsCoordinator->setSystemSignature<TestSystem>(signature);
		
		// Maak een entity en voeg components toe
		auto entity = ecsCoordinator->createEntity("Test Entity");
		ecsCoordinator->addComponent<Transform>(entity, { glm::vec3(69, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0) });
		ecsCoordinator->addComponent<PerspectiveCamera>(entity, {});
		ecsCoordinator->addComponent<OrthographicCamera>(entity, {});
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