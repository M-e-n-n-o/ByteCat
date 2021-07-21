#include <ByteCat.h>
#include "imgui/imgui.h"

using namespace BC;


class ExampleLayer : public Layer
{
private:
	std::shared_ptr<GameObject> object;
	std::shared_ptr<GameObject> camera;

public:
	ExampleLayer() : Layer("ExampleLayer")
	{
		std::vector<float> vertices =
		{
		  -0.5f, 0.5f, 0,
		  -0.5f, -0.5f, 0,
		  0.5f, -0.5f, 0,
		  0.5f, 0.5f, 0
		};

		std::vector<unsigned int> indices =
		{
			0,1,3,
			3,1,2
		};

		std::vector<float> textureCoords =
		{
			0, 0,
			0, 1,
			1, 1,
			1, 0
		};
		
		std::shared_ptr<Shader> shader = Shaders::Create(ByteCatShader::Standard);
		std::shared_ptr<Texture2D> texture = Texture2D::Create("kat.jpg");
		shader->setTexture(texture);
		
		object = GameLayer::CreateGameObject("TestObject", Transform({ 0, 0, -1 }, { 0, 0, 0 }, { 1, 1, 1 }));
		object->addComponent(new Mesh(vertices, indices, textureCoords));
		object->addComponent(new MeshRenderer());
		object->addComponent(new Material(shader));

		camera = GameLayer::CreateGameObject("Camera", Transform({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }));
		camera->addComponent(new PerspectiveCamera(70, 0.01f, 1000));
		GameLayer::SetCamera(camera);
	}

	void onUpdate() override
	{
		object->transform.position.z -= Application::GetDelta() * 0.5f;
	}

	void onImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void onEvent(Event& event) override
	{
		if (event.getEventType() == EventType::KeyPressed)
		{
			event.handled = true;
			KeyPressedEvent& e = (KeyPressedEvent&) event;
			if (e.getKeyCode() == KeyCode::Backspace)
			{
				LOG_INFO("Backspace is pressed");
				
			}
			LOG_INFO("{0}", (char)e.getKeyCode());
		}
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