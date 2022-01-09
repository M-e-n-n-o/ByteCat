#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"

namespace BC
{
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");

        Renderer::SetAPI(GraphicsAPI::OpenGL);
		      
        WindowSettings setting = { "ByteCat Engine", 1280, 720, false };
        window = Window::Create(setting);
        window->setEventListener(this);
        
        Renderer::Init(new SimpleRenderer());
	}

    Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");

        Renderer::Shutdown();
        delete window;
    }

    void Application::start()
    {
        if (isRunning)
        {
            LOG_WARN("Cannot run the main game loop synchronous");
            return;
        }
		
        isRunning = true;    	
		
        run();
    }
	
	void Application::run()
	{
		const char* vertexSource = R"(
			#version 330 core

			layout (location = 0) in vec3 vertexPos;
		
			void main()
			{
				gl_Position = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0);
			}
		)";

		const char* fragmentSource = R"(
			#version 330 core

			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			}
		)";
		
		auto shader = Shader::Create("Test", vertexSource, fragmentSource);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2
		};

		auto vao = VertexArray::Create();

		auto ebo = IndexBuffer::Create(indices, sizeof(indices));
		vao->setIndexBuffer(ebo);

		auto vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = { { ShaderDataType::Float3, "vertexPos" } };
		vbo->setLayout(layout);
		vao->addVertexBuffer(vbo);
		
		while (isRunning)
		{
			window->update();

			if (window->isMinimized())
			{
				continue;
			}

		 	// Updating
	        for (Layer* layer : layerStack)
	        {
				if (layer->enabled) { layer->onUpdate(); }
	        }

            Renderer::Submit({ vao, shader });
			
            // Rendering
            for (Layer* layer : layerStack)
            {
                if (layer->enabled) { layer->onRender(); }
            }

            Renderer::RenderFrame({});
		}
	}

    void Application::onEvent(Event& event)
    {		
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(BC_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(BC_BIND_EVENT_FN(Application::onWindowResize));
		
        for (auto it = layerStack.end(); it != layerStack.begin();)
        {
            --it;
        	
            if ((*it)->enabled)
            {
                (*it)->onEvent(event);
                if (event.handled)
                {
                    break;
                }
            }
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        isRunning = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& event)
    {
        window->resize(event.getWidth(), event.getHeight());
        Renderer::SetViewport(0, 0, event.getWidth(), event.getHeight());
    	
        return true;
    }

    void Application::pushLayer(Layer* layer)
    {
        layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer* overlay)
    {
        layerStack.pushOverlay(overlay);
    }
}
