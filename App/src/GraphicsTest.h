#pragma once
#include <ByteCat.h>

using namespace BC;
using namespace App;
using namespace Inputs;

class GraphicsTest : public Layer
{
	std::shared_ptr<EcsCoordinator> ecsCoordinator;

	Entity camera;
	Entity doggo;

	std::shared_ptr<FrameBuffer> fbo;
	std::shared_ptr<Renderable> fboRenderable;

public:	
	GraphicsTest() : Layer("Graphics Test")
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

		// Skybox cubemap
		auto skyboxTexture = TextureCube::Create({ "skybox/right.jpg", "skybox/left.jpg", "skybox/top.jpg", "skybox/bottom.jpg", "skybox/front.jpg", "skybox/back.jpg" });

		auto skyboxShader = Shader::Create("SkyboxShader", "skybox/SkyboxVertex.glsl", "skybox/SkyboxFragment.glsl", true);
		skyboxShader->setTextureSlots({ "skybox" });

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

		// Quad
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

		auto dogTexture = Texture2D::Create("dog.png");
		auto standardShader = Shader::Create("StandardShader", "SimpleVertex.glsl", "SimpleFragment.glsl", true);
		standardShader->setTextureSlots({ "tex" });

		// Framebuffer
		auto& window = Application::GetInstance().getWindow();
		fbo = FrameBuffer::Create("Test", window.getWidth(), window.getHeight());
		auto colorAttachment = Texture2D::Create(window.getWidth(), window.getHeight(), TextureFormat::RGB8);
		fbo->attachTexture(colorAttachment);
		fbo->attachRenderBuffer(TextureFormat::DEPTH16);
		fbo->unbind();

		auto fboShader = Shader::Create("Fbo shader", "FboVertex.glsl", "FboFragment.glsl", true);
		fboShader->setTextureSlots({ "screenTexture" });

		std::vector<std::shared_ptr<Texture>> textures = { colorAttachment };
		fboRenderable = std::make_shared<Renderable>(CullingMode::Back, quad, fboShader, textures, Math::CreateModelMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

		// Entities toevoegen
		camera = ecsCoordinator->createEntity("Camera");
		ecsCoordinator->addComponent<Transform>(camera, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1) });
		ecsCoordinator->addComponent<PerspectiveCamera>(camera, { 70, 0.1f, 1000.0f });

		for (int i = -30; i < 30; i += 5)
		{
			doggo = ecsCoordinator->createEntity("Doggo");
			ecsCoordinator->addComponent<Transform>(doggo, { glm::vec3(i, 0, -10), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2) });
			ecsCoordinator->addComponent<Mesh>(doggo, { quad });
			ecsCoordinator->addComponent<Material>(doggo, { CullingMode::Back, standardShader, { dogTexture } });
		}

		auto skyboxEntity = ecsCoordinator->createEntity("Skybox");
		ecsCoordinator->addComponent<Transform>(skyboxEntity, { glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(900, 900, 900) });
		ecsCoordinator->addComponent<Mesh>(skyboxEntity, { cubeVao });
		ecsCoordinator->addComponent<Material>(skyboxEntity, { CullingMode::Front, skyboxShader, {skyboxTexture} });
	}

	void onUpdate() override
	{
		Transform* cam = ecsCoordinator->getComponent<Transform>(camera);
		cam->rotation.y += Time::GetDeltaTime() * 50;

		Renderer::Submit(fboRenderable);
	}

	void beforeRender() override
	{
		RendererAPI::SetDepthTest(true);
		Renderer::Render();
		fbo->unbind();

		Renderer::Submit(fboRenderable);
		RendererAPI::SetDepthTest(false);
	}

	void onRenderComplete() override
	{
		fbo->bind();
	}

	void onGuiRender() override
	{

	}

	void onEvent(Event& event) override
	{

	}
};