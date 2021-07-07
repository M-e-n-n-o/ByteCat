#include "bcpch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "byteCat/app/Window.h"
#include "byteCat/app/Application.h"
#include "byteCat/input/events/ApplicationEvent.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/input/events/MouseEvent.h"

namespace BC
{
	GLFWwindow* nativeWindow;
	
	Window::Window(WindowSetting& windowSetting)
	{
		LOG_INFO("Creating a window");

		setting = windowSetting;

		if (!glfwInit())
		{
			return;
		}

		nativeWindow = glfwCreateWindow(setting.width, setting.height, setting.title.c_str(), NULL, NULL);
		if (!nativeWindow)
		{
			LOG_CRITICAL("Failed to create a window with OpenGL context");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(nativeWindow);
		
		const int error = glewInit();
		if (error)
		{
			LOG_CRITICAL("Failed to initialize glew");
			std::exit(-1);
		}

		LOG_INFO("OpenGL Info:");
		LOG_INFO("   Vendor:   {0}", glGetString(GL_VENDOR));
		LOG_INFO("   Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("   Version:  {0}", glGetString(GL_VERSION));

		if (!GLEW_VERSION_4_5)
		{
			LOG_CRITICAL("ByteCat requires at least OpenGL version 4.5");
			std::exit(-1);
		}
		
		setVsync(windowSetting.vSync);

		glfwSetWindowSizeCallback(nativeWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent event(width, height);
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* window)
		{
			WindowCloseEvent event;
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetKeyCallback(nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(static_cast<KeyCode>(key), false);
				Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(static_cast<KeyCode>(key));
				Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent event(static_cast<KeyCode>(key), true);
				Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				break;
			}
			}
		});

		glfwSetCharCallback(nativeWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetMouseButtonCallback(nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(static_cast<MouseCode>(button));
				Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
				Application::GetInstance().getWindow().getEventListener()->onEvent(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetCursorPosCallback(nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			MouseMovedEvent event((float)xPos, (float)yPos);
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});
	}

	double Window::update() const
	{	
		glfwSwapBuffers(nativeWindow);
		glfwPollEvents();

		const double currentTime = glfwGetTime();
		static double lastFrameTime = 0;
		const double deltaTime = (currentTime - lastFrameTime);
		lastFrameTime = currentTime;

		// Calculate and print fps
		static long lastFps = 0;
		static long fps = 0;
		if (glfwGetTime() - lastFps > 10)
		{
			LOG_INFO("Fps {0}", fps);
			fps = 0;
			lastFps += 10;
		}

		fps++;
		
		return deltaTime;
	}

	void Window::shutdown() const
	{
		glfwDestroyWindow(nativeWindow);
		glfwTerminate();
	}

	void Window::resize(unsigned int width, unsigned int height)
	{
		setting.width = width;
		setting.height = height;
	}

	void Window::setVsync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		setting.vSync = enabled;
	}

	void* Window::getNativeWindow() const
	{
		return nativeWindow;
	}
}
