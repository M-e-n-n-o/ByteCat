#include "bcpch.h"
#include <GL/glew.h>
#include "byteCat/app/Application.h"

#include "byteCat/render/models/Texture.h"
#include "byteCat/render/shaders/Shader.h"
#include "byteCat/utils/Math.h"
#include "byteCat/render/vertex-object/Buffer.h"
#include "byteCat/render/vertex-object/VertexArray.h"

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

		
        std::shared_ptr<VertexArray> vao = VertexArray::Create();
		
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->setBufferType({ ShaderDataType::Float3 });
        vao->addVertexBuffer(vertexBuffer);

        std::shared_ptr<VertexBuffer> textureBuffer = VertexBuffer::Create(textureCoords, sizeof(textureCoords));
        textureBuffer->setBufferType({ ShaderDataType::Float2 });
        vao->addVertexBuffer(textureBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices));
        vao->setIndexBuffer(indexBuffer);

		
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
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

            shader->bind();
            shader->loadMatrix4("modelMatrix", Utils::CreateModelMatrix(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
            vao->bind();
            shader->bindTextures();
            glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
            vao->unbind();
            shader->unbind();
			
			
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
