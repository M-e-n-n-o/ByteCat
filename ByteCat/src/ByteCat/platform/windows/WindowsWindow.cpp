#include "bcpch.h"
#include "WindowsWindow.h"

#include "byteCat/Application.h"
#include "byteCat/events/ApplicationEvent.h"
#include "byteCat/events/KeyEvent.h"
#include "byteCat/events/MouseEvent.h"

namespace BC
{	
	WindowsWindow::WindowsWindow(WindowSetting& windowSetting)
	{
		BC_INFO("Creating a Windows window");

		setting = windowSetting;
		
		if (!glfwInit())
		{
			return;
		}

		window = glfwCreateWindow(setting.width, setting.height, setting.title.c_str(), NULL, NULL);
		if (!window)
		{
			BC_CRITICAL("Failed to create a windows window with OpenGL context");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		setVsync(windowSetting.vSync);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent event(width, height);
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowCloseEvent event;
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
		{
			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
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

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
		{
			MouseMovedEvent event((float) xPos, (float) yPos);
			Application::GetInstance().getWindow().getEventListener()->onEvent(event);
		});
	}

	void WindowsWindow::update()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::setVsync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		} else
		{
			glfwSwapInterval(0);
		}

		setting.vSync = enabled;
	}
}
