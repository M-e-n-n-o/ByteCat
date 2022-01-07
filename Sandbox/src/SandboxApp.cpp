#include <ByteCat.h>

using namespace BC;

class ExampleLayer : public Layer
{
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<VertexArray> vao;
	
public:
	ExampleLayer() : Layer("ExampleLayer")
	{

	}

	void onUpdate() override
	{		

	}

	void onRender() override
	{
		//Renderer::Submit({ vao, shader });
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