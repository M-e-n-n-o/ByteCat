#pragma once

#include "byteCat/inputs/EventCallback.h"
#include "byteCat/inputs/events/Event.h"

#if defined(BC_PLATFORM_PC)
	#include "platform/winLin/WinLinPcInputModule.h"
#elif defined(BC_PLATFORM_MOBILE)
	#include "platform/mobile/MobileInputModule.h"
#endif

namespace BC
{
	namespace Inputs
	{		
		class EmptyInputModule {};

		/**
		 * @brief
		 * Use this class to poll inputs, start/stop listening to specific Events or send out Events to all listeners
		 * 
		 * @tparam InputModule The inputmodule you want to use as your input (e.g. PcInputModule, or your own module)
		 */
#if defined(BC_PLATFORM_PC)
		template<class InputModule = PcInputModule>
#elif defined(BC_PLATFORM_MOBILE)
		template<class InputModule = MobileInputModule>
#else
		template<class InputModule = EmptyInputModule>
#endif
		class Input : public InputModule
		{
		private:
			inline static std::vector<std::shared_ptr<EventCallback>> s_callbacks;
			
		public:
			// All the new events used to call callbacks with will need to be received here
			static void HandleEvent(const Event& event);

			// Call this function to add a callback to a specified key code, returns the id of the callback
			static int StartListening(EventCallback* callback);

			// Call this function to remove a callback
			static void StopListening(int& id);
		};

		
		//-----------------------------------------------------------------------------------------------------------------
		//									Template function definitions
		// -----------------------------------------------------------------------------------------------------------------
		
		template <class InputModule>
		void Input<InputModule>::HandleEvent(const Event& event)
		{
			for (const auto& callback : s_callbacks)
			{
				if (*callback == event)
				{
					callback->callback(event);
				}
			}
		}

		template <class InputModule>
		int Input<InputModule>::StartListening(EventCallback* callback)
		{
			s_callbacks.push_back(std::shared_ptr<EventCallback>(callback));
			return s_callbacks.size() - 1;
		}

		template <class InputModule>
		void Input<InputModule>::StopListening(int& id)
		{
			if (id < s_callbacks.size() && id >= 0)
			{
				s_callbacks.erase(s_callbacks.begin() + id);
				id = -1;
			}
		}
	}
}
