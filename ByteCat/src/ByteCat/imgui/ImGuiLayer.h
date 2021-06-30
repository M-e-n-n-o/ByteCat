#pragma once

#include "byteCat/Core.h"
#include "byteCat/app/Layer.h"

namespace BC
{
	class BYTECAT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() : Layer("ImGuiLayer") {}
		~ImGuiLayer() = default;

		void begin();
		void end();
		
		void onAttach() override;
		void onDetach() override;
		void onImGuiRender() override;
	};
}
