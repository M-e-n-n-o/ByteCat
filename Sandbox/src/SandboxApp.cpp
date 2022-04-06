#include <ByteCat.h>
#include "TestLayer.h"

using namespace BC;

class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox(): Application()
	{
        Renderer::SetAPI(GraphicsAPI::OpenGL);

        WindowSettings settings = { "Sandbox App", 1280, 720, true };
        m_window = Window::Create(settings);
        m_window->setEventListener(this);

        Renderer::Init(new SimpleRenderer());
		
		pushLayer(new TestLayer());
	}

	// The end of your application
	~Sandbox() override
	{
		Renderer::Shutdown();
		delete m_window;
	}
};

Application* BC::CreateApplication()
{
	return new Sandbox();
}