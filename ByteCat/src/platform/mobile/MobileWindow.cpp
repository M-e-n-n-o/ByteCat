#ifdef BC_PLATFORM_MOBILE
#include "bcpch.h"
#include <glfm.h>
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/mobile/MobileWindow.h"
#include "byteCat/inputs/KeyCodes.h"
#include "byteCat/inputs/events/ApplicationEvent.h"
#include "byteCat/inputs/events/KeyEvent.h"
#include "byteCat/inputs/events/TouchEvent.h"

namespace BC
{	
	namespace Platform
	{
		static Inputs::EventListener* eventListener;
		static GLFMDisplay* nativeWindow;
		static bool isInFocus = true;
		static unsigned int windowWidth;
		static unsigned int windowHeight;
		
		MobileWindow::MobileWindow(Graphics::WindowSettings settings, void* appInputData)
		{			
			LOG_INFO("Trying to initialize the Android window");
			
			if (Graphics::Renderer::GetAPI() != Graphics::GraphicsAPI::OpenGLES)
			{
				LOG_CRITICAL("Unsupported Graphics API for Android platform selected!");
			}
			
			GLFMColorFormat colorFormat = GLFMColorFormatRGBA8888;
			switch (settings.colorFormat)
			{
				case Graphics::WindowSettings::ColorFormat::RGBA8888: colorFormat = GLFMColorFormatRGBA8888; break;
				case Graphics::WindowSettings::ColorFormat::RGB565: colorFormat = GLFMColorFormatRGB565; break;
				default: LOG_WARN("Color format not supported or selected! Choosing default..."); ;
			}
			
			GLFMDepthFormat depthFormat = GLFMDepthFormatNone;
			switch (settings.depthFormat)
			{
				case Graphics::WindowSettings::DepthFormat::None: depthFormat = GLFMDepthFormatNone; break;
				case Graphics::WindowSettings::DepthFormat::D16: depthFormat = GLFMDepthFormat16; break;
				case Graphics::WindowSettings::DepthFormat::D24: depthFormat = GLFMDepthFormat24; break;
				default: LOG_WARN("Depth format not supported or selected! Choosing default..."); ;
			}
			
			GLFMStencilFormat stencilFormat = GLFMStencilFormatNone;
			switch (settings.stencilFormat)
			{
				case Graphics::WindowSettings::StencilFormat::None: stencilFormat = GLFMStencilFormatNone; break;
				case Graphics::WindowSettings::StencilFormat::S8: stencilFormat = GLFMStencilFormat8; break;
				default: LOG_WARN("Stencil format not supported or selected! Choosing default..."); ;
			}
			
			GLFMMultisample multisample = GLFMMultisampleNone;
			switch (settings.multisample)
			{
				case Graphics::WindowSettings::Multisample::None: multisample = GLFMMultisampleNone; break;
				case Graphics::WindowSettings::Multisample::M4x: multisample = GLFMMultisample4X; break;
				default: LOG_WARN("Multisample option not supported or selected! Choosing default..."); ;
			}

			nativeWindow = static_cast<GLFMDisplay*>(appInputData);
			
			glfmSetDisplayConfig(nativeWindow, GLFMRenderingAPIOpenGLES32, colorFormat, depthFormat, stencilFormat, multisample);
			
			glfmSetSurfaceCreatedFunc(nativeWindow, [](GLFMDisplay* display, int width, int height)
				{
					windowWidth = width;
					windowHeight = height;

					GLFMRenderingAPI api = glfmGetRenderingAPI(display);
					LOG_INFO("Configured Android window with OpenGLES version %s",
						api == GLFMRenderingAPIOpenGLES32 ? "ES 3.2" :
						api == GLFMRenderingAPIOpenGLES31 ? "ES 3.1" :
						api == GLFMRenderingAPIOpenGLES3 ? "ES 3.0" : "ES 2.0");

					if (api < GLFMRenderingAPIOpenGLES32)
					{
						LOG_CRITICAL("ByteCat requires at least OpenGLES version 3.2");
						std::exit(-1);
					}
				});
			
			
			glfmSetSurfaceDestroyedFunc(nativeWindow, [](GLFMDisplay* display)
				{
					Inputs::WindowCloseEvent event;
					eventListener->onEvent(event);
				});

			glfmSetOrientationChangedFunc(nativeWindow, [](GLFMDisplay* display, GLFMInterfaceOrientation orientation)
				{
					int width, height = 0;
					glfmGetDisplaySize(nativeWindow, &width, &height);
					windowWidth = width;
					windowHeight = height;
				
					Inputs::WindowResizeEvent event(width, height);
					eventListener->onEvent(event);
				});

			glfmSetAppFocusFunc(nativeWindow, [](GLFMDisplay* display, bool focused)
				{
					isInFocus = focused;

					if (focused)
					{
						Inputs::WindowOnFocusEvent event;
						eventListener->onEvent(event);
						return;
					}

					Inputs::WindowLostFocusEvent event;
					eventListener->onEvent(event);
					return;
				});
			
			glfmSetRenderFunc(nativeWindow, [](GLFMDisplay* display)
				{
					// glClearColor(1, 0, 0, 1);
					// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
					// Graphics::Renderer::GetRenderer()->clearColor(glm::vec4(1, 0, 0, 1));
					// Graphics::Renderer::GetRenderer()->clearBuffers();
				
					Inputs::WindowRenderEvent event;
					eventListener->onEvent(event);
				});

			glfmSetKeyFunc(nativeWindow, [](GLFMDisplay* display, GLFMKey keyCode, GLFMKeyAction action, int modifiers)
				{
					switch (action)
					{
						case GLFMKeyActionPressed:
						{
							Inputs::KeyPressedEvent event(static_cast<Inputs::KeyCode>(keyCode), false);
							eventListener->onEvent(event);
							break;
						}

						case GLFMKeyActionReleased:
						{
							Inputs::KeyReleasedEvent event(static_cast<Inputs::KeyCode>(keyCode));
							eventListener->onEvent(event);
							break;
						}

						case GLFMKeyActionRepeated:
						{
							Inputs::KeyPressedEvent event(static_cast<Inputs::KeyCode>(keyCode), true);
							eventListener->onEvent(event);
							break;
						}
					}

					return true;
				});

			glfmSetTouchFunc(nativeWindow, [](GLFMDisplay* display, int touch, GLFMTouchPhase phase, double x, double y)
				{				
					switch(phase)
					{
						case GLFMTouchPhaseHover:
						{
							Inputs::TouchHoverEvent event(glm::vec2(x, y));
							eventListener->onEvent(event);
							break;
						}

						case GLFMTouchPhaseBegan:
						{
							Inputs::TouchBeganEvent event(glm::vec2(x, y));
							eventListener->onEvent(event);
							break;
						}

						case GLFMTouchPhaseMoved:
						{
							Inputs::TouchMovedEvent event(glm::vec2(x, y));
							eventListener->onEvent(event);
							break;
						}

						case GLFMTouchPhaseEnded:
						{
							Inputs::TouchEndedEvent event(glm::vec2(x, y));
							eventListener->onEvent(event);
							break;
						}

						case GLFMTouchPhaseCancelled:
						{
							Inputs::TouchCancelledEvent event(glm::vec2(x, y));
							eventListener->onEvent(event);
							break;
						}
					}

					return true;
				});
		}

		MobileWindow::~MobileWindow()
		{
			// Nothing for now
		}

		void MobileWindow::update() const
		{
			glfmSwapBuffers(nativeWindow);
		}

		void MobileWindow::shutdown() const
		{
			// Nothing for now
		}

		void MobileWindow::resize(unsigned width, unsigned height)
		{
			// Does nothing
		}

		std::string MobileWindow::getTitle() const
		{
			return "";
		}

		unsigned MobileWindow::getWidth() const
		{
			return windowWidth;
		}

		unsigned MobileWindow::getHeight() const
		{
			return windowHeight;
		}

		void MobileWindow::setVsync(bool enabled)
		{
			// Does nothing
		}

		bool MobileWindow::getVsync() const
		{
			// Does nothing
			return false;
		}

		bool MobileWindow::isMinimized()
		{
			return !isInFocus;
		}

		void MobileWindow::captureMouse(bool capture)
		{
			// Does nothing
		}

		void* MobileWindow::getNativeWindow() const
		{
			return (void*) nativeWindow;
		}

		void MobileWindow::setEventListener(Inputs::EventListener* newListener)
		{
			eventListener = newListener;
		}
	}
}

#endif