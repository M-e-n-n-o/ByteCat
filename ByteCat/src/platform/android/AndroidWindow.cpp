#ifdef BC_PLATFORM_MOBILE
#include "bcpch.h"
#include <glfm.h>
#include "byteCat/graphics/renderer/Renderer.h"
#include "platform/android/AndroidWindow.h"

#include <string.h>

namespace BC
{	
	namespace Platform
	{

		static GLint program = 0;
		static GLuint vertexBuffer = 0;

		static GLuint compileShader(const GLenum type, const GLchar* shaderString) {
			const GLint shaderLength = (GLint)strlen(shaderString);
			GLuint shader = glCreateShader(type);
			glShaderSource(shader, 1, &shaderString, &shaderLength);
			glCompileShader(shader);
			return shader;
		}
		
		AndroidWindow::AndroidWindow(Graphics::WindowSettings settings, void* appInputData)
		{			
			LOG_INFO("Trying to initialize the Android window");
			//
			// if (Graphics::Renderer::GetAPI() != Graphics::GraphicsAPI::OpenGLES)
			// {
			// 	LOG_CRITICAL("Unsupported Graphics API for Android platform selected!");
			// }
			//
			// GLFMColorFormat colorFormat = GLFMColorFormatRGBA8888;
			// switch (settings.colorFormat)
			// {
			// case Graphics::WindowSettings::ColorFormat::RGBA8888: colorFormat = GLFMColorFormatRGBA8888; break;
			// case Graphics::WindowSettings::ColorFormat::RGB565: colorFormat = GLFMColorFormatRGB565; break;
			// default: LOG_WARN("Color format not supported or selected! Choosing default..."); ;
			// }
			//
			// GLFMDepthFormat depthFormat = GLFMDepthFormatNone;
			// switch (settings.depthFormat)
			// {
			// case Graphics::WindowSettings::DepthFormat::None: depthFormat = GLFMDepthFormatNone; break;
			// case Graphics::WindowSettings::DepthFormat::D16: depthFormat = GLFMDepthFormat16; break;
			// case Graphics::WindowSettings::DepthFormat::D24: depthFormat = GLFMDepthFormat24; break;
			// default: LOG_WARN("Depth format not supported or selected! Choosing default..."); ;
			// }
			//
			// GLFMStencilFormat stencilFormat = GLFMStencilFormatNone;
			// switch (settings.stencilFormat)
			// {
			// case Graphics::WindowSettings::StencilFormat::None: stencilFormat = GLFMStencilFormatNone; break;
			// case Graphics::WindowSettings::StencilFormat::S8: stencilFormat = GLFMStencilFormat8; break;
			// default: LOG_WARN("Stencil format not supported or selected! Choosing default..."); ;
			// }
			//
			// GLFMMultisample multisample = GLFMMultisampleNone;
			// switch (settings.multisample)
			// {
			// case Graphics::WindowSettings::Multisample::None: multisample = GLFMMultisampleNone; break;
			// case Graphics::WindowSettings::Multisample::M4x: multisample = GLFMMultisample4X; break;
			// default: LOG_WARN("Multisample option not supported or selected! Choosing default..."); ;
			// }

			GLFMDisplay* display = static_cast<GLFMDisplay*>(appInputData);

			glfmSetDisplayConfig(display,
				GLFMRenderingAPIOpenGLES2,
				GLFMColorFormatRGBA8888,
				GLFMDepthFormatNone,
				GLFMStencilFormatNone,
				GLFMMultisampleNone);
			
			// glfmSetDisplayConfig(display, GLFMRenderingAPIOpenGLES32, colorFormat, depthFormat, stencilFormat, multisample);
			
			glfmSetSurfaceCreatedFunc(display, [](GLFMDisplay* display, int width, int height)
				{
					glViewport(0, 0, width, height);
				});
			
			glfmSetSurfaceDestroyedFunc(display, [](GLFMDisplay* display)
				{
					program = 0;
					vertexBuffer = 0;
				});
			
			glfmSetRenderFunc(display, [](GLFMDisplay* display)
				{
					if (program == 0) {
						const GLchar* vertexShader =
							"attribute highp vec4 position;\n"
							"void main() {\n"
							"   gl_Position = position;\n"
							"}";

						const GLchar* fragmentShader =
							"void main() {\n"
							"  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
							"}";

						program = glCreateProgram();
						GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertexShader);
						GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

						glAttachShader(program, vertShader);
						glAttachShader(program, fragShader);

						glLinkProgram(program);

						glDeleteShader(vertShader);
						glDeleteShader(fragShader);
					}
					if (vertexBuffer == 0) {
						const GLfloat vertices[] = {
							 0.0,  0.5, 0.0,
							-0.5, -0.5, 0.0,
							 0.5, -0.5, 0.0,
						};
						glGenBuffers(1, &vertexBuffer);
						glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
					}

					glClearColor(0.4f, 0.0f, 0.6f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT);

					glUseProgram(program);
					glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
					glDrawArrays(GL_TRIANGLES, 0, 3);

					glfmSwapBuffers(display);
				});
		}

		AndroidWindow::~AndroidWindow()
		{
		}

		void AndroidWindow::update() const
		{
		}

		void AndroidWindow::shutdown() const
		{
		}

		void AndroidWindow::resize(unsigned width, unsigned height)
		{
		}

		std::string AndroidWindow::getTitle() const
		{
		}

		unsigned AndroidWindow::getWidth() const
		{
		}

		unsigned AndroidWindow::getHeight() const
		{
		}

		void AndroidWindow::setVsync(bool enabled)
		{
		}

		bool AndroidWindow::getVsync() const
		{
		}

		bool AndroidWindow::isMinimized()
		{
		}

		void AndroidWindow::captureMouse(bool capture)
		{
		}

		void* AndroidWindow::getNativeWindow() const
		{
		}

		void AndroidWindow::setEventListener(Inputs::EventListener* newListener)
		{
		}
	}
}

#endif