#pragma once
#ifdef BC_PLATFORM_ANDROID
#include "byteCat/imgui/ImGuiLayer.h"

namespace BC
{
	namespace Platform
	{
		class AndroidImGuiRenderer : public Imgui::ImGuiRenderer
		{
		public:
			AndroidImGuiRenderer() = default;
			~AndroidImGuiRenderer() = default;

			void enable() override;
			void disable() override;

			void begin() override;
			void end() override;
		};
	}
}
#endif