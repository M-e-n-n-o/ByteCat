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
		// static GLint program = 0;
		// static GLuint vertexBuffer = 0;
		//
		// static GLuint compileShader(const GLenum type, const GLchar* shaderString) {
		// 	const GLint shaderLength = (GLint)strlen(shaderString);
		// 	GLuint shader = glCreateShader(type);
		// 	glShaderSource(shader, 1, &shaderString, &shaderLength);
		// 	glCompileShader(shader);
		// 	return shader;
		// }

		static Inputs::EventListener* eventListener;
		static GLFMDisplay* nativeWindow;
		
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
					glViewport(0, 0, width, height);

					GLFMRenderingAPI api = glfmGetRenderingAPI(display);
					LOG_INFO("Configured Android window with OpenGLES version %s",
						api == GLFMRenderingAPIOpenGLES32 ? "ES 3.2" :
						api == GLFMRenderingAPIOpenGLES31 ? "ES 3.1" :
						api == GLFMRenderingAPIOpenGLES3 ? "ES 3.0" : "ES 2.0");
				});
			
			
			glfmSetSurfaceDestroyedFunc(nativeWindow, [](GLFMDisplay* display)
				{
					Inputs::WindowCloseEvent event;
					eventListener->onEvent(event);
				});

			glfmSetRenderFunc(nativeWindow, [](GLFMDisplay* display)
				{
		// 					if (program == 0) {
		// 	const GLchar* vertexShader =
		// 		"attribute highp vec4 position;\n"
		// 		"void main() {\n"
		// 		"   gl_Position = position;\n"
		// 		"}";
		//
		// 	const GLchar* fragmentShader =
		// 		"void main() {\n"
		// 		"  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		// 		"}";
		//
		// 	program = glCreateProgram();
		// 	GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertexShader);
		// 	GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
		//
		// 	glAttachShader(program, vertShader);
		// 	glAttachShader(program, fragShader);
		//
		// 	glLinkProgram(program);
		//
		// 	glDeleteShader(vertShader);
		// 	glDeleteShader(fragShader);
		// }
		// if (vertexBuffer == 0) {
		// 	const GLfloat vertices[] = {
		// 		 0.0,  0.5, 0.0,
		// 		-0.5, -0.5, 0.0,
		// 		 0.5, -0.5, 0.0,
		// 	};
		// 	glGenBuffers(1, &vertexBuffer);
		// 	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// }
		//
		// glClearColor(0.4f, 0.0f, 0.6f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		//
		// glUseProgram(program);
		// glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		//
		// glEnableVertexAttribArray(0);
		// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		//
		// glfmSwapBuffers(display);
				
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
			
			// glfmSetRenderFunc(display, [](GLFMDisplay* display)
			// 	{
			// 		if (program == 0) {
			// 			const GLchar* vertexShader =
			// 				"attribute highp vec4 position;\n"
			// 				"void main() {\n"
			// 				"   gl_Position = position;\n"
			// 				"}";
			//
			// 			const GLchar* fragmentShader =
			// 				"void main() {\n"
			// 				"  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
			// 				"}";
			//
			// 			program = glCreateProgram();
			// 			GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertexShader);
			// 			GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
			//
			// 			glAttachShader(program, vertShader);
			// 			glAttachShader(program, fragShader);
			//
			// 			glLinkProgram(program);
			//
			// 			glDeleteShader(vertShader);
			// 			glDeleteShader(fragShader);
			// 		}
			// 		if (vertexBuffer == 0) {
			// 			const GLfloat vertices[] = {
			// 				 0.0,  0.5, 0.0,
			// 				-0.5, -0.5, 0.0,
			// 				 0.5, -0.5, 0.0,
			// 			};
			// 			glGenBuffers(1, &vertexBuffer);
			// 			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			// 			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			// 		}
			//
			// 		glClearColor(0.4f, 0.0f, 0.6f, 1.0f);
			// 		glClear(GL_COLOR_BUFFER_BIT);
			//
			// 		glUseProgram(program);
			// 		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			//
			// 		glEnableVertexAttribArray(0);
			// 		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			// 		glDrawArrays(GL_TRIANGLES, 0, 3);
			//
			// 		glfmSwapBuffers(display);
			// 	});
		}

		MobileWindow::~MobileWindow()
		{
		}

		void MobileWindow::update() const
		{
		}

		void MobileWindow::shutdown() const
		{
		}

		void MobileWindow::resize(unsigned width, unsigned height)
		{
		}

		std::string MobileWindow::getTitle() const
		{
		}

		unsigned MobileWindow::getWidth() const
		{
		}

		unsigned MobileWindow::getHeight() const
		{
		}

		void MobileWindow::setVsync(bool enabled)
		{
		}

		bool MobileWindow::getVsync() const
		{
		}

		bool MobileWindow::isMinimized()
		{
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