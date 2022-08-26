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
	Sandbox(void* appInputData): Application()
	{		
        Renderer::SetAPI(GraphicsAPI::OpenGL);

		WindowSettings settings = { "Sandbox App", 1280, 720, true };
		// WindowSettings settings = { WindowSettings::ColorFormat::RGBA8888, WindowSettings::DepthFormat::None, WindowSettings::StencilFormat::None, WindowSettings::Multisample::None };
		
        m_window = Window::Create(settings, appInputData);
        m_window->setEventListener(this);

        Renderer::Init();
		
		//pushLayer(new GraphicsTest());
	}

	// The end of your application
	~Sandbox() override
	{
		Renderer::Shutdown();
		delete m_window;
	}
};

Application* App::CreateApplication(void* data)
{
	return new Sandbox(data);
}