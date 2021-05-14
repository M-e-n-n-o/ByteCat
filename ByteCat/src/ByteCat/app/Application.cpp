#include "bcpch.h"
#include "byteCat/app/Application.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/render/Loader.h"
#include "byteCat/render/Renderer.h"
#include "byteCat/render/shaders/StaticShader.h"

namespace BC
{
    Application* Application::instance = nullptr;
	
	Application::Application() : isRunning(false)
	{
        LOG_ASSERT(!instance, "Application already exists!");
        instance = this;
		
        LOG_INFO("ByteCat engine is starting...");
		
        WindowSetting setting = { "ByteCat Engine", 1280, 720, true };
        window = new Window(setting);
        window->setEventListener(this);
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
        StaticShader shader;
        shader.init();
		
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
        RawModel model = Loader::LoadToVAO(vertices, textureCoords, indices);
        ModelTexture texture = { Loader::LoadTexture("res/blokje.png") };
        TexturedModel texturedModel = { model, texture };
		
		while (isRunning)
        {
            Renderer::Prepare();
            shader.start();
            Renderer::Render(texturedModel);
            shader.stop();
			
            // Update
            update();

            window->update();
        }

        Loader::CleanUp();
	}

    void Application::onEvent(Event& event)
    {		
        switch (event.getEventType())
        {
        case EventType::WindowClose:
	        {
				isRunning = false;
                break;
	        }
        }
    }

	Application::~Application()
    {
        LOG_INFO("ByteCat engine is closing...");
		
        delete window;
    }
}
