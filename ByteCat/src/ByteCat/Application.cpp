#include "bcpch.h"
#include "byteCat/Application.h"
#include "events/KeyEvent.h"

namespace BC
{
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        BC_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        BC_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = Window::Create(setting);
        window->setEventListener(this);
	}

	void Application::run()
	{
		if (isRunning)
		{
            BC_ERROR("Cannot run the main game loop synchronous");
            return;
		}
        
        isRunning = true;
		
		while (isRunning)
        {
            // Update
            update();

            // Render
            render();

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
        BC_INFO("ByteCat engine is closing...");
		
        delete window;
    }
}
