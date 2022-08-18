#ifdef BC_PLATFORM_PC
#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "platform/winLin/WinLinWindow.h"
#include "byteCat/inputs/events/ApplicationEvent.h"
#include "byteCat/inputs/events/KeyEvent.h"
#include "byteCat/inputs/events/MouseEvent.h"

namespace BC
{
	namespace Platform
	{
		static GLFWwindow* nativeWindow;
		static Inputs::EventListener* eventListener;
		
		WinLinWindow::WinLinWindow(const Graphics::WindowSettings& setting)
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

			m_context = Graphics::GraphicsContext::Create(nativeWindow);
			m_context->init(m_windowSetting.width, m_windowSetting.height);

			setVsync(m_windowSetting.vSync);


			glfwSetWindowSizeCallback(nativeWindow, [](GLFWwindow* window, int width, int height)
				{
					Inputs::WindowResizeEvent event(width, height);
					eventListener->onEvent(event);
				});

			glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow* window)
				{
					Inputs::WindowCloseEvent event;
					eventListener->onEvent(event);
				});

			glfwSetKeyCallback(nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					switch (action)
					{
					case GLFW_PRESS:
					{
						Inputs::KeyPressedEvent event(static_cast<Inputs::KeyCode>(key), false);
						eventListener->onEvent(event);
						break;
					}

					case GLFW_RELEASE:
					{
						Inputs::KeyReleasedEvent event(static_cast<Inputs::KeyCode>(key));
						eventListener->onEvent(event);
						break;
					}

					case GLFW_REPEAT:
					{
						Inputs::KeyPressedEvent event(static_cast<Inputs::KeyCode>(key), true);
						eventListener->onEvent(event);
						break;
					}
					}
				});

			glfwSetCharCallback(nativeWindow, [](GLFWwindow* window, unsigned int keycode)
				{
					Inputs::KeyTypedEvent event(static_cast<Inputs::KeyCode>(keycode));
					eventListener->onEvent(event);
				});

			glfwSetMouseButtonCallback(nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
				{
					switch (action)
					{
					case GLFW_PRESS:
					{
						Inputs::MouseButtonPressedEvent event(static_cast<Inputs::MouseCode>(button));
						eventListener->onEvent(event);
						break;
					}
					case GLFW_RELEASE:
					{
						Inputs::MouseButtonReleasedEvent event(static_cast<Inputs::MouseCode>(button));
						eventListener->onEvent(event);
						break;
					}
					}
				});

			glfwSetScrollCallback(nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					Inputs::MouseScrolledEvent event((float)xOffset, (float)yOffset);
					eventListener->onEvent(event);
				});

			glfwSetCursorPosCallback(nativeWindow, [](GLFWwindow* window, double xPos, double yPos)
				{
					Inputs::MouseMovedEvent event((float)xPos, (float)yPos);
					eventListener->onEvent(event);
				});
		}

		void WinLinWindow::update() const
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

		void WinLinWindow::captureMouse(bool capture)
		{
			if (capture)
			{
				glfwSetInputMode(nativeWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			} else
			{
				glfwSetInputMode(nativeWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}

		void* WinLinWindow::getNativeWindow() const
		{
			return (void*) nativeWindow;
		}

		void WinLinWindow::setEventListener(Inputs::EventListener* newListener)
		{
			eventListener = newListener;
		}
	}
}
#endif