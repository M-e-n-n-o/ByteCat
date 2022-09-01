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
        Renderer::SetAPI(GraphicsAPI::OpenGLES);

		//WindowSettings settings = { "Sandbox App", 1280, 720, true };
		WindowSettings settings = { WindowSettings::ColorFormat::RGBA8888, WindowSettings::DepthFormat::None, WindowSettings::StencilFormat::None, WindowSettings::Multisample::None };
		
        m_window = Window::Create(settings, appInputData);
        m_window->setEventListener(this);
		

		/*
		* OpenGL calls werken gok ik niet totdat de "SurfaceCreatedFunc" is aangeroepen van MobileWindow.
		* Hierdoor gaan waarschijnlijk dus ook niet de debug messages aan.
		* Dus we moeten wachten totdat die functie is aangeroepen en dan pas doorgaan naar na deze comment.
		* (Hopelijk fixed dat ook het texture probleem)
		*/


        Renderer::Init();
		
		Utils::Utility::RequestPermissions({ "READ_EXTERNAL_STORAGE", "WRITE_EXTERNAL_STORAGE" });

		pushLayer(new GraphicsTest());
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