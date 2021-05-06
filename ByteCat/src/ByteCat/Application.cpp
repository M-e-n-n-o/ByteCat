#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "byteCat/Application.h"
#include "events/KeyEvent.h"

namespace BC
{
	Application::Application() : isRunning(false)
	{
        BC_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = Window::Create(setting);
        window->setEventListener(this);
	}

	void Application::run()
	{
		if (isRunning)
		{
            BC_INFO("Cannot run the main game loop synchronous");
            return;
		}
        
        isRunning = true;
		
		while (isRunning)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            // Update
            update();

            // Render
            render();
            glBegin(GL_TRIANGLES);
            glVertex2d(-0.5f, -0.5f);
            glVertex2d(0.0f, 0.5f);
            glVertex2d(0.5f, -0.5f);
            glEnd();

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
