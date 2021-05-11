#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/events/KeyEvent.h"
#include "byteCat/render/Loader.h"
#include "byteCat/render/Renderer.h"

namespace BC
{
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = new Window(setting);
        window->setEventListener(this);
	}

    void Application::start()
    {
        if (isRunning)
        {
            LOG_WARN("Cannot run the main game loop synchronous");
            return;
        }
        isRunning = true;

        run();
    }

	void Application::run()
	{	
        std::vector<float> vertices =
        {
		  -0.5f, 0.5f, 0,
		  -0.5f, -0.5f, 0,
		  0.5f, -0.5f, 0,
		  0.5f, 0.5f, 0
        };

        std::vector<int> indices =
        {
            0,1,3,
			3,1,2
        };
        RawModel model = Loader::LoadToVAO(vertices, indices);
		
		while (isRunning)
        {
            Renderer::Prepare();

            Renderer::Render(model);
			
            // Update
            update();

            window->update();
        }
	}

    void Application::onEvent(Event& event)
    {		
        switch (event.getEventType())
        {
        case EventType::WindowClose:
	        {
				isRunning = false;
                break;
	        }
        }
    }

	Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");

        Loader::CleanUp();
		
        delete window;
    }
}
