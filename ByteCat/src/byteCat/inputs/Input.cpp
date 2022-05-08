#include "bcpch.h"
#include "byteCat/inputs/Input.h"

namespace BC
{
	namespace Inputs
	{
		void Input::HandleEvent(const Event& event)
		{
			for (const auto& callback : s_callbacks)
			{
				if (*callback == event)
				{
					callback->callback(event);
				}
			}
		}

		void Input::StartListening(std::shared_ptr<EventCallback> callback)
		{
			s_callbacks.push_back(callback);
		}
		
		void Input::StopListening(std::shared_ptr<EventCallback> toDelete)
		{
			s_callbacks.erase(std::remove_if(s_callbacks.begin(), s_callbacks.end(), [&toDelete](const std::shared_ptr<EventCallback>& other)
			{
				return *other == *toDelete;
			}), s_callbacks.end());
		}

		void Input::AddCustomKeyCode(const std::string& name, const KeyCode& code)
		{
			s_customKeyCodes.insert({name, code});
		}

		bool Input::IsKeyPressed(const std::string& customKey)
		{
			const auto value = s_customKeyCodes.find(customKey);
			
			if (value == s_customKeyCodes.end())
			{
				LOG_ERROR("Custom key: {0} does not exist", customKey);
				return false;
			}

			return IsKeyPressed(value->second);
		}
	}
}
