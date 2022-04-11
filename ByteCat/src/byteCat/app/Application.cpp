#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/ecs/SceneManager.h"
#include "byteCat/graphics/renderer/Renderer.h"
#include "byteCat/imgui/ImGuiLayer.h"
#include "byteCat/app/Time.h"

namespace BC
{
    namespace App
    {
        Application* Application::s_instance = nullptr;

        Application::Application() : m_isRunning(false)
        {
            LOG_ASSERT(!s_instance, "Application already exists!");
            s_instance = this;

            LOG_INFO("ByteCat engine is starting...");
        }

        Application::~Application()
        {
            LOG_INFO("ByteCat engine is closing...");
        }

        void Application::start()
        {        	
            m_isRunning = true;

            m_imguiLayer = new Imgui::ImGuiLayer();
            pushLayer(m_imguiLayer);
            pushLayer(new Time());

            while (m_isRunning)
            {
                m_window->update();

                if (m_window->isMinimized())
                {
                    continue;
                }

                for (Layer* layer : m_layerStack)
                {
                    if (layer->m_enabled) { layer->onUpdate(); }
                }

                for (Layer* layer : m_layerStack)
                {
                    if (layer->m_enabled) { layer->onRender(); }
                }

                Graphics::Renderer::RenderSubmissions();

                for (Layer* layer : m_layerStack)
                {
                    if (layer->m_enabled) { layer->onRenderComplete(); }
                }

                if (m_imguiLayer->m_enabled)
                {
                    m_imguiLayer->begin();
                    for (Layer* layer : m_layerStack)
                    {
                        if (layer->m_enabled) { layer->onGuiRender(); }
                    }
                    m_imguiLayer->end();
                }
            }
        }

        void Application::onEvent(Inputs::Event& event)
        {
	        Inputs::EventDispatcher dispatcher(event);
            dispatcher.dispatch<Inputs::WindowCloseEvent>(BC_BIND_EVENT_FN(Application::onWindowClose));
            dispatcher.dispatch<Inputs::WindowResizeEvent>(BC_BIND_EVENT_FN(Application::onWindowResize));

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

        bool Application::onWindowClose(Inputs::WindowCloseEvent& event)
        {
            m_isRunning = false;
            return true;
        }

        bool Application::onWindowResize(Inputs::WindowResizeEvent& event)
        {
            m_window->resize(event.getWidth(), event.getHeight());
            Graphics::Renderer::SetViewport(0, 0, event.getWidth(), event.getHeight());

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
}
