#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "byteCat/Application.h"
#include "byteCat/input/KeyCodes.h"
#include "events/KeyEvent.h"

namespace BC
{
    static GLFWwindow* window;
	
	Application::Application()
	{
        BC_INFO("ByteCat engine is starting...");
		
        if (!glfwInit())
            return;

        window = glfwCreateWindow(1280, 720, "ByteCat Engine", NULL, NULL);
        if (!window)
        {
            BC_CRITICAL("Failed to create window with OpenGL context");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
	}

	void Application::run()
	{
        static bool isRunning = false;
		if (isRunning)
		{
            BC_INFO("Cannot run the main game loop synchronous");
            return;
		}
        
        isRunning = true;
		
        while (!glfwWindowShouldClose(window))
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
        	
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
		
        isRunning = false;
	}

    void Application::onEvent(Event& event)
    {
        BC_INFO("Got an event!");
		try
		{
			auto& keyEvent = dynamic_cast<KeyPressedEvent&>(event);
            BC_INFO(keyEvent.getKeyCode());
			
        } catch (const std::bad_cast& e)
        {
            BC_INFO("Not a key event");
        }
    }

    Application::~Application()
    {
        BC_INFO("ByteCat engine is closing...");
        glfwTerminate();
    }
}
