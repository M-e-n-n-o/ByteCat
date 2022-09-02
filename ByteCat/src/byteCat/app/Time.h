#pragma once
#include "byteCat/app/Layer.h"

namespace BC
{
	namespace App
	{
		class Time : public Layer
		{
		private:
			inline static float s_deltaTime;
			inline static float s_lastFrameTime = 0;

		public:
			Time() : Layer("Time") {}

			void onUpdate() override;

			void onEvent(Inputs::Event& event) override;

			static float GetDeltaTime() { return s_deltaTime; }
		};
	}
}
