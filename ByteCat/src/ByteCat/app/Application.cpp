#include "bcpch.h"
#include "byteCat/app/Application.h"

#include "byteCat/entity-system/Mesh.h"
#include "byteCat/render/textures/Texture.h"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/render/Renderer.h"


namespace BC
{	
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = Window::Create(setting);
        window->setEventListener(this);

        gameObjectLayer = new GameObjectLayer();
        pushLayer(gameObjectLayer);
		
        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);

        Renderer::Init();
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
        float vertices[] =
        {
		  -0.5f, 0.5f, 0,
		  -0.5f, -0.5f, 0,
		  0.5f, -0.5f, 0,
		  0.5f, 0.5f, 0
        };
   
        unsigned int indices[] =
        {
            0,1,3,
			3,1,2
        };
   
        float textureCoords[] =
        {
        	0, 0,
        	0, 1,
        	1, 1,
        	1, 0
        };
		
        std::shared_ptr<Shader> shader = Shader::Create(ByteCatShader::Standard);
        std::shared_ptr<Texture2D> texture = Texture2D::Create("blokje.png");
        shader->setTexture(texture);
		
        std::shared_ptr<GameObject> object = GameObjectLayer::CreateGameObject();
        object->addComponent(new Mesh(vertices, sizeof(vertices), indices, sizeof(indices), textureCoords, sizeof(textureCoords)));
		
		
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
            Renderer::BeginScene();
			
            Renderer::Submit(shader, object->getComponentOfType<Mesh>()->getVao(), object->getModelMatrix());
			
            Renderer::EndScene();
			
			
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
        Renderer::OnWindowResize(event.getWidth(), event.getHeight());

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
