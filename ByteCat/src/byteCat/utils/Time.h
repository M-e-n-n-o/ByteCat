#pragma once
#include "byteCat/app/Layer.h"

namespace BC
{
	class Time : public Layer
	{
	private:		
		inline static float s_deltaTime;
	
	public:
		Time(): Layer("Time") {}

		void onUpdate() override;

		static float GetDeltaTime() { return s_deltaTime; }
	};
}
