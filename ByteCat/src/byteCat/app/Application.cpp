#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"
#include "glad/glad.h"
#include "platform/CommandExecutor.h"

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

	void runMainLoop(Window* window, LayerStack& layerStack, bool& isRunning)
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
                if (layer->m_enabled) { layer->onUpdate(); }
            }


            // Heave duty test code
			for (int k = 0; k < 15000; k++)
			{
			    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
			    int n = sizeof(arr) / sizeof(arr[0]);
			
			    int i, j;
			    for (i = 0; i < n - 1; i++)
			    {
			        for (j = 0; j < n - i - 1; j++)
			        {
			            if (arr[j] > arr[j + 1])
			            {
			                //swap(&arr[j], &arr[j + 1]);
			                int temp = arr[j];
			                arr[j] = arr[j + 1];
			                arr[j + 1] = temp;
			            }
			        }
			    }
			}
        	

            Platform::CommandExecutor::Sync();

            for (int i = 0; i < 200; i++)
            {
                Renderer::Submit({ vao, shader });
            }
            
            // Rendering
            for (Layer* layer : layerStack)
            {
                if (layer->m_enabled) { layer->onRender(); }
            }
            
            Renderer::RenderFrame({});
        }

        Platform::CommandExecutor::Shutdown();
	}
	
    void Application::start()
    {		
        m_isRunning = true;

        LOG_INFO("Multithreaded platform backend: {0}", c_multithreaded);
		
		if (c_multithreaded)
		{			
            std::thread logicThread(runMainLoop, m_window, std::ref(m_layerStack), std::ref(m_isRunning));
            Platform::CommandExecutor::Start(true);
            logicThread.join();
		} else
		{
            Platform::CommandExecutor::Start(false);
            runMainLoop(m_window, m_layerStack, m_isRunning);
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
