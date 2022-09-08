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
		//WindowSettings settings = { WindowSettings::ColorFormat::RGBA8888, WindowSettings::DepthFormat::D16, WindowSettings::StencilFormat::None, WindowSettings::Multisample::None };
		
        m_window = Window::Create(settings, appInputData);
        m_window->setEventListener(this);
		
		//Utils::Utility::RequestPermissions({ "READ_EXTERNAL_STORAGE", "WRITE_EXTERNAL_STORAGE" });
	}

	// You can have Graphics API calls from here on out (not in constructor)
	void onApplicationStart() override
	{
		Renderer::Init();
		pushLayer(new GraphicsTest());
		//pushLayer(new VisualisatieTechnieken());
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