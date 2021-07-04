#pragma once

#include "byteCat/app/Layer.h"

namespace BC
{
	/*
	 * Class ImGuiLayer:
	 *		This layer class starts and stops the imGui rendering
	 */
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer() : Layer("ImGuiLayer") {}
		~ImGuiLayer() = default;

		void begin();
		void end();
		
		void onAttach() override;
		void onDetach() override;
	};
}
