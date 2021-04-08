#include "bcpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace ByteCat
{
    static GLFWwindow* window;

	Application::Application()
	{
        /* Initialize the library */
        if (!glfwInit())
            return;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(1280, 720, "ByteCat Engine", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
	}

	Application::~Application()
	{
        glfwTerminate();
	}

	void Application::run()
	{
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
	}
}