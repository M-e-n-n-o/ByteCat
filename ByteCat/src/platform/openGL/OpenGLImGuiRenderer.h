#pragma once
#ifdef BC_PLATFORM_PC
#include "byteCat/imgui/ImGuiLayer.h"

namespace BC
{
	namespace Platform
	{
		class OpenGLImGuiRenderer : public Imgui::ImGuiRenderer
		{
		public:
			OpenGLImGuiRenderer() = default;
			~OpenGLImGuiRenderer() = default;

			void enable() override;
			void disable() override;
			
			void begin() override;
			void end() override;
		};
	}
}
#endif