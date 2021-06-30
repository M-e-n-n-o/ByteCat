#pragma once

#include "byteCat/Core.h"
#include "byteCat/app/Layer.h"

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
	};
}
