#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/ecs/SceneManager.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/graphics/renderer/elaborations/SimpleRenderer.h"
#include "byteCat/utils/Time.h"

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

        m_logicLayer = new SceneManager();
        pushLayer(m_logicLayer);
        m_timeLayer = new Time();
        pushLayer(m_timeLayer);
	}

    Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");

        Renderer::Shutdown();
        delete m_window;
    }
	
    void Application::start()
    {		
        m_isRunning = true;

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

            // Rendering
            for (Layer* layer : m_layerStack)
            {
                if (layer->m_enabled) { layer->onRender(); }
            }

            Renderer::RenderFrame();

            for (Layer* layer : m_layerStack)
            {
                if (layer->m_enabled) { layer->onRenderComplete(); }
            }
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
