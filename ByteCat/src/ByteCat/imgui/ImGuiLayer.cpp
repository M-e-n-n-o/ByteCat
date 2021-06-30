#include "bcpch.h"
#include <GLFW/glfw3.h>
#include "byteCat/imgui/ImGuiLayer.h"
#include "imgui.h"
#include "byteCat/app/Application.h"
#include "byteCat/imgui/ImGuiRenderer.h"

namespace BC
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
		
	}

	ImGuiLayer::~ImGuiLayer()
	{
		
	}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach()
	{
		
	}
	 
	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetInstance();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());
		
		float time = (float) glfwGetTime();
		io.DeltaTime = prevTime > 0.0f ? (time - prevTime) : (1.0f / 60.0f);
		prevTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseButtonPressedEvent>(BC_BIND_EVENT_FN(onMouseButtonPressed));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BC_BIND_EVENT_FN(onMouseButtonReleased));
		dispatcher.dispatch<MouseMovedEvent>(BC_BIND_EVENT_FN(onMouseMoved));
		dispatcher.dispatch<MouseScrolledEvent>(BC_BIND_EVENT_FN(onMouseScrolled));
		dispatcher.dispatch<KeyPressedEvent>(BC_BIND_EVENT_FN(onKeyPressed));
		dispatcher.dispatch<KeyReleasedEvent>(BC_BIND_EVENT_FN(onKeyReleased));
		dispatcher.dispatch<KeyTypedEvent>(BC_BIND_EVENT_FN(onKeyTyped));
		dispatcher.dispatch<WindowResizeEvent>(BC_BIND_EVENT_FN(onWindowResize));
	}

	bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[static_cast<int>(event.getMouseButton())] = true;
		return false;
	}
	
	bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[static_cast<int>(event.getMouseButton())] = false;
		return false;
	}
	
	bool ImGuiLayer::onMouseMoved(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.getMouseX(), event.getMouseY());
		return false;
	}
	
	bool ImGuiLayer::onMouseScrolled(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.getOffsetX();
		io.MouseWheel += event.getOffsetY();
		return false;
	}
	
	bool ImGuiLayer::onKeyPressed(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[static_cast<int>(event.getKeyCode())] = true;

		io.KeyCtrl = io.KeysDown[static_cast<int>(KeyCode::LeftControl)] || io.KeysDown[static_cast<int>(KeyCode::RightControl)];
		io.KeyShift = io.KeysDown[static_cast<int>(KeyCode::LeftShift)] || io.KeysDown[static_cast<int>(KeyCode::RightShift)];
		io.KeyAlt = io.KeysDown[static_cast<int>(KeyCode::LeftAlt)] || io.KeysDown[static_cast<int>(KeyCode::RightAlt)];
		io.KeySuper = io.KeysDown[static_cast<int>(KeyCode::LeftSuper)] || io.KeysDown[static_cast<int>(KeyCode::RightSuper)];
		
		return false;
	}
	
	bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[static_cast<int>(event.getKeyCode())] = false;
		return false;
	}
	
	bool ImGuiLayer::onKeyTyped(KeyTypedEvent& event)
	{		
		ImGuiIO& io = ImGui::GetIO();
		int keyCode = static_cast<int>(event.getKeyCode());
		if (keyCode > 0 && keyCode < 0x10000)
		{
			io.AddInputCharacter((unsigned short) keyCode);
		}
		
		return false;
	}
	
	bool ImGuiLayer::onWindowResize(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		
		return false;
	}
}
