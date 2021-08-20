#include "bcpch.h"
#include "byteCat/app/Application.h"

#include "byteCat/entity-system/Material.h"
#include "byteCat/entity-system/renderers/Mesh.h"
#include "byteCat/entity-system/cameras/PerspectiveCamera.h"
#include "byteCat/render/Renderer.h"


namespace BC
{	
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, false };
        window = Window::Create(setting);
        window->setEventListener(this);

        gameLayer = new GameLayer();
        pushLayer(gameLayer);
		
        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);

        Renderer::Init();
	}

    Application::~Application()
    {
        Renderer::Shutdown();
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
		while (isRunning)
		{
            delta = window->update();
			
            if (isMinimized) { continue; }
			
		 	// Updating
	        for (Layer* layer : layerStack)
	        {
				if (layer->enabled) { layer->onUpdate(); }
	        }

			
            // Rendering
            if (std::shared_ptr<GameObject> camera = gameLayer->GetCamera())
            {
                Renderer::BeginScene(camera->getComponent<Camera>()->getViewMatrix(), camera->getComponent<Camera>()->getProjectionMatrix());

            	// OnRender
                for (Layer* layer : layerStack)
                {
                    if (layer->enabled) { layer->onRender(); }
                }
            	
                for (std::shared_ptr<GameObject>& gameObject : gameLayer->getGameObjects())
                {
                    if (gameObject->isEnabled) { Renderer::Submit(gameObject); }
                }

                Renderer::EndScene();
            } else
            {
                LOG_WARN("No camera has been set");
            }
		 	
		 	
		 	// ImGui Rendering
            if (imGuiLayer->enabled)
            {
                imGuiLayer->begin();
                for (Layer* layer : layerStack)
				{
					if (layer->enabled) { layer->onImGuiRender(); }
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
		if (event.getWidth() == 0 || event.getHeight() == 0)
		{
            isMinimized = true;
            return false;
		}

        isMinimized = false;

        window->resize(event.getWidth(), event.getHeight());
        Renderer::OnWindowResize(event.getWidth(), event.getHeight());
        gameLayer->onWindowResize(event.getWidth(), event.getHeight());

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
