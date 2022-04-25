#include <ByteCat.h>
#include "VisualisatieTechnieken.h"
#include "GraphicsTest.h"

using namespace BC;
using namespace App;
using namespace Graphics;

class Sandbox : public Application
{
public:
	// The start of your application
	Sandbox(): Application()
	{
        Renderer::SetAPI(GraphicsAPI::OpenGL);
		
        WindowSettings settings = { "Sandbox App", 1280, 720, true };
        m_window = Window::Create(settings);
        m_window->setEventListener(this);

        Renderer::Init();
		
		pushLayer(new VisualisatieTechnieken());
	}

	// The end of your application
	~Sandbox() override
	{
		Renderer::Shutdown();
		delete m_window;
	}
};

Application* App::CreateApplication()
{
	return new Sandbox();
}