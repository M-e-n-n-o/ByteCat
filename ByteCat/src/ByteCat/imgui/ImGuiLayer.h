#pragma once

#include "byteCat/Core.h"
#include "byteCat/app/Layer.h"
#include "byteCat/input/events/ApplicationEvent.h"
#include "byteCat/input/events/KeyEvent.h"
#include "byteCat/input/events/MouseEvent.h"

namespace BC
{
	class BYTECAT_API ImGuiLayer : public Layer
	{
	private:
		float prevTime = 0.0f;
	
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(Event& event) override;

	private:
		bool onMouseButtonPressed(MouseButtonPressedEvent& event);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool onMouseMoved(MouseMovedEvent& event);
		bool onMouseScrolled(MouseScrolledEvent& event);
		bool onKeyPressed(KeyPressedEvent& event);
		bool onKeyReleased(KeyReleasedEvent& event);
		bool onKeyTyped(KeyTypedEvent& event);
		bool onWindowResize(WindowResizeEvent& event);
	};
}
