#pragma once
#include "byteCat/app/Layer.h"

namespace BC
{
	class ImGuiRenderer
	{
	public:
		virtual ~ImGuiRenderer() = default;

		virtual void enable() = 0;
		virtual void disable() = 0;
		
		virtual void begin() = 0;
		virtual void end() = 0;

		static std::shared_ptr<ImGuiRenderer> Create();
	};
	
	class ImGuiLayer : public Layer
	{
	private:
		std::shared_ptr<ImGuiRenderer> m_renderer;
		
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void begin();
		void end();

		void onAttach() override;
		void onDetach() override;
	};
}
