#pragma once
#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
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