#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"

#include "platform/PlatformAPI.h"

namespace BC
{
    Application* Application::s_instance = nullptr;
	
	Application::Application() : m_isRunning(false)
	{
        LOG_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;
		
        LOG_INFO("ByteCat engine is starting...");

        Renderer::SetAPI(GraphicsAPI::OpenGL);
		      
        WindowSettings setting = { "ByteCat Engine", 1280, 720, false };
        m_window = Window::Create(setting);
        m_window->setEventListener(this);
        
        Renderer::Init(new SimpleRenderer());
	}

    Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");

        Renderer::Shutdown();
        delete m_window;
    }


    void addCommands(int threadNumber)
	{
		for (int i = 0; i < 50; i++)
		{
            Platform::API::PushCommand([number = threadNumber, i]() { LOG_INFO("{0} printed number: {1}", number, i); });
		}

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        Platform::API::Shutdown();
	}
	
    void Application::start()
    {		      
        std::thread first(addCommands, 1);
        std::thread second(addCommands, 2);
        std::thread third(addCommands, 3);

        Platform::API::Start();

        first.join();
        second.join();
        third.join();

        return;
		
		
        if (m_isRunning)
        {
            LOG_WARN("Cannot run the main game loop synchronous");
            return;
        }
		
        m_isRunning = true;    	
		
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
		
		while (m_isRunning)
		{
			m_window->update();

			if (m_window->isMinimized())
			{
				continue;
			}

		 	// Updating
	        for (Layer* layer : m_layerStack)
	        {
				if (layer->m_enabled) { layer->onUpdate(); }
	        }

            Renderer::Submit({ vao, shader });
			
            // Rendering
            for (Layer* layer : m_layerStack)
            {
                if (layer->m_enabled) { layer->onRender(); }
            }

            Renderer::RenderFrame({});
		}
	}

    void Application::onEvent(Event& event)
    {		
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(BC_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(BC_BIND_EVENT_FN(Application::onWindowResize));
		
        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            --it;
        	
            if ((*it)->m_enabled)
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
        m_isRunning = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& event)
    {
        m_window->resize(event.getWidth(), event.getHeight());
        Renderer::SetViewport(0, 0, event.getWidth(), event.getHeight());
    	
        return true;
    }

    void Application::pushLayer(Layer* layer)
    {
        m_layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer* overlay)
    {
        m_layerStack.pushOverlay(overlay);
    }
}
