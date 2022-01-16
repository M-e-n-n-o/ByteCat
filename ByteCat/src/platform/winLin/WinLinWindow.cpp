#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "platform/winLin/WinLinWindow.h"

#include "byteCat/input/events/ApplicationEvent.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/input/events/MouseEvent.h"
#include "platform/PlatformAPI.h"

namespace BC
{
	namespace Platform
	{
		static GLFWwindow* nativeWindow;
		static EventListener* eventListener;
		
		WinLinWindow::WinLinWindow(WindowSettings& setting)
		{
			LOG_INFO("Trying to create a Windows/Linux window");

			m_windowSetting = setting;

			if (!glfwInit())
			{
				LOG_CRITICAL("Could not initialize GLFW");
				std::exit(-1);
			}

			nativeWindow = glfwCreateWindow(m_windowSetting.width, m_windowSetting.height, m_windowSetting.title.c_str(), NULL, NULL);
			if (m_windowSetting.width == 0 || m_windowSetting.height == 0)
			{
				m_isMinimized = true;
			}
			else
			{
				m_isMinimized = false;
			}

			if (!nativeWindow)
			{
				LOG_CRITICAL("Failed to create a Windows/Linux window");
				glfwTerminate();
				std::exit(-1);
			}

			LOG_INFO("Created a Windows/Linux window with title: {0}, width: {1}, height: {2} and vSync: {3}", m_windowSetting.title, m_windowSetting.width, m_windowSetting.height, m_windowSetting.vSync);

			m_context = GraphicsContext::Create(nativeWindow);
			m_context->init(m_windowSetting.width, m_windowSetting.height);

			setVsync(m_windowSetting.vSync);

			
			glfwSetWindowSizeCallback(nativeWindow, [](GLFWwindow* window, int width, int height)
				{
					WindowResizeEvent event(width, height);
					eventListener->onEvent(event);
				});

			glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* window)
				{
					WindowCloseEvent event;
					eventListener->onEvent(event);
				});

			glfwSetKeyCallback(nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					switch (action)
					{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), false);
						eventListener->onEvent(event);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(static_cast<KeyCode>(key));
						eventListener->onEvent(event);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyPressedEvent event(static_cast<KeyCode>(key), true);
						eventListener->onEvent(event);
						break;
					}
					}
				});

			glfwSetCharCallback(nativeWindow, [](GLFWwindow* window, unsigned int keycode)
				{
					KeyTypedEvent event(static_cast<KeyCode>(keycode));
					eventListener->onEvent(event);
				});

			glfwSetMouseButtonCallback(nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
				{
					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(static_cast<MouseCode>(button));
						eventListener->onEvent(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
						eventListener->onEvent(event);
						break;
					}
					}
				});

			glfwSetScrollCallback(nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					MouseScrolledEvent event((float)xOffset, (float)yOffset);
					eventListener->onEvent(event);
				});

			glfwSetCursorPosCallback(nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
				{
					MouseMovedEvent event((float)xPos, (float)yPos);
					eventListener->onEvent(event);
				});
		}

		void WinLinWindow::update() const
		{
			API::PushCommand([this]()
			{	
				m_context->swapBuffers();
				glfwPollEvents();

				const double currentTime = glfwGetTime();
				static double lastFrameTime = 0;
				const double deltaTime = (currentTime - lastFrameTime);
				lastFrameTime = currentTime;

				// Calculate and print fps
				static long lastFps = 0;
				static long fps = 0;
				if (glfwGetTime() - lastFps > 3)
				{
					LOG_INFO("Fps {0}", fps / 3);
					fps = 0;
					lastFps += 3;
				}

				fps++;
			});
		}

		void WinLinWindow::shutdown() const
		{
			delete m_context;
			glfwDestroyWindow(nativeWindow);
			glfwTerminate();
		}

		void WinLinWindow::resize(unsigned int width, unsigned int height)
		{
			m_windowSetting.width = width;
			m_windowSetting.height = height;

			if (width == 0 || height == 0)
			{
				m_isMinimized = true;
			}
			else
			{
				m_isMinimized = false;
			}
		}

		void WinLinWindow::setVsync(bool enabled)
		{
			m_windowSetting.vSync = enabled;
			
			if (enabled)
			{
				glfwSwapInterval(1);
			}
			else
			{
				glfwSwapInterval(0);
			}
		}

		void* WinLinWindow::getNativeWindow() const
		{
			return (void*) nativeWindow;
		}

		void WinLinWindow::setEventListener(EventListener* newListener)
		{
			eventListener = newListener;
		}
	}
}
