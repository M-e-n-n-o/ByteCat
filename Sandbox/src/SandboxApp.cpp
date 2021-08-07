#include <ByteCat.h>

#include "byteCat/render/Renderer.h"
#include "imgui/imgui.h"

#include "CameraControls.h"

using namespace BC;

class ExampleLayer : public Layer
{
private:
	std::shared_ptr<GameObject> object;
	std::shared_ptr<GameObject> camera;

public:
	ExampleLayer() : Layer("ExampleLayer")
	{		
		std::shared_ptr<Shader> shader = Shaders::Create(ByteCatShader::Standard);
		std::shared_ptr<Texture2D> texture = Texture2D::Create("TreeTexture.png");
		shader->setTexture(texture);


		// Dit moet straks maar 1 keer gebeuren als je bijvoorbeeld 10x zegt dat ik het Tree.obj model wil gebruiken als de mesh.
		// 
		// Hiervoor moet dus een soort van object storage komen waar alle vao's en model data worden opgeslagen. Wel moet het een mogelijkheid
		// zijn om een nieuwe vao te maken voor een model wat al eerder is gemaakt zodat er een mogelijkheid blijft om de data van het
		// model aan te passen zonder dat de rest ook aangepast wordt.
			std::vector<float> vertices;
			std::vector<unsigned int> indices;
			std::vector<float> normals;
			std::vector<float> textureCoords;
			ModelLoader::LoadModel("Tree.obj", vertices, indices, normals, textureCoords);


			auto vao = VertexArray::Create();

			std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.data(), (unsigned)(sizeof(float) * vertices.size()));
			vertexBuffer->setBufferType({ ShaderDataType::Float3 });
			vao->addVertexBuffer(vertexBuffer);

			std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords.data(), (unsigned)(sizeof(float) * textureCoords.size()));
			textureBuffer->setBufferType({ ShaderDataType::Float2 });
			vao->addVertexBuffer(textureBuffer);

			std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), (unsigned)indices.size());
			vao->setIndexBuffer(indexBuffer);
		//
		

		
		for (int i = -100; i < 100; i += 1)
		{
			object = GameLayer::CreateGameObject("Tree", Transform({ i, -5, -100 }, { 0, 0, 0 }, { 0.5, 0.5, 0.5 }));
			object->addComponent(new Mesh(vao));
			object->addComponent(new MeshRenderer());			
			object->addComponent(new Material(shader));
		}
		
		camera = GameLayer::CreateGameObject("Camera", Transform({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }));
		camera->addComponent(new PerspectiveCamera(70, 0.01f, 1000));
		camera->addComponent(new CameraControls);

		GameLayer::SetCamera(camera);
	}

	void onUpdate() override
	{
		object->transform.rotation.y += Application::GetDelta() * 10;
	}

	void onImGuiRender() override
	{
		ImGui::Begin("Test Window");
		ImGui::Text("Hello World");
		float v[2] = {0, 1};
		ImGui::SliderFloat2("Prachtige sliders", v, -10, 10);
		ImGui::End();
	}

	void onEvent(Event& event) override
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