#include "bcpch.h"
#include "byteCat/app/Application.h"

#include "byteCat/render/Renderer.h"
#include "byteCat/render/models/Mesh.h"
#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/render/shaders/StandardShader.h"
#include "byteCat/utils/Maths.h"

namespace BC
{	
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = std::make_unique<Window>(setting);
        window->setEventListener(this);

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
	}

    Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");
    }

    void Application::start()
    {
        if (isRunning)
        {
            LOG_WARN("Cannot run the main game loop synchronous");
            return;
        }
        isRunning = true;
        isMinimized = false;

        run();
    }
	
	void Application::run()
	{	
        std::vector<float> vertices =
        {
		  -0.5f, 0.5f, 0,
		  -0.5f, -0.5f, 0,
		  0.5f, -0.5f, 0,
		  0.5f, 0.5f, 0
        };
   
        std::vector<int> indices =
        {
            0,1,3,
			3,1,2
        };
   
        std::vector<float> textureCoords =
        {
        	0, 0,
        	0, 1,
        	1, 1,
        	1, 0
        };
   
        Mesh mesh(vertices, textureCoords, indices);
        Texture2D texture("blokje.png");
		 
        StandardShader shader(texture);
        Renderer renderer;
		
		while (isRunning)
		{
            window->update();
			
            if (isMinimized) { continue; }

			// Updating
            for (Layer* layer : layerStack)
            {
                if (layer->isEnabled()) { layer->onUpdate(); }
            }

			// Rendering
            renderer.prepare();

			shader.begin();
			shader.loadMatrix4("modelMatrix", Utils::CreateModelMatrix(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
			renderer.renderVAO(*mesh.vao, shader);
			shader.end();
			
			// ImGui Rendering
            if (imGuiLayer->isEnabled())
            {
                imGuiLayer->begin();
                for (Layer* layer : layerStack)
                {
                    if (layer->isEnabled()) { layer->onImGuiRender(); }
                }
                imGuiLayer->end();
            }
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
        	
            if ((*it)->isEnabled())
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
		if (event.getWidth() == 0 || event.getHeight() == 0)
		{
            isMinimized = true;
            return false;
		}

        isMinimized = false;

        window->resize(event.getWidth(), event.getHeight());

        return false;
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
