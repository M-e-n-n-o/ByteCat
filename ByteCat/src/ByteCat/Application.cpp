#include "bcpch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Application.h"
#include "Log.h"

namespace ByteCat
{
    static GLFWwindow* window;

	Application::Application()
	{
        if (!glfwInit())
            return;

        window = glfwCreateWindow(1280, 720, "ByteCat Engine", NULL, NULL);
        if (!window)
        {
            BC_CORE_CRITICAL("Failed to create window with OpenGL context");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
	}

	void Application::run()
	{
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            // Update
            onUpdate();

            // Render
            onRender();
            glBegin(GL_TRIANGLES);
            glVertex2d(-0.5f, -0.5f);
            glVertex2d(0.0f, 0.5f);
            glVertex2d(0.5f, -0.5f);
            glEnd();
        	
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
	}

    Application::~Application()
    {
        glfwTerminate();
    }
}