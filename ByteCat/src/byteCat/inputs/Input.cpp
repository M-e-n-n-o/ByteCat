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

		int Input::StartListening(EventCallback* callback)
		{
			s_callbacks.push_back(std::shared_ptr<EventCallback>(callback));
			return s_callbacks.size() - 1;
		}
		
		void Input::StopListening(int& id)
		{			
			if (id < s_callbacks.size() && id >= 0)
			{
				s_callbacks.erase(s_callbacks.begin() + id);
				id = -1;
			}
		}

		void Input::AddCustomKeyCode(const std::string& name, const CodeType& code)
		{
			s_customKeyCodes.insert({ name, std::vector<CodeType>() });
			s_customKeyCodes[name].push_back(code);
		}

		bool Input::IsPressed(const std::string& customKey)
		{
			const auto value = s_customKeyCodes.find(customKey);
			
			if (value == s_customKeyCodes.end())
			{
				LOG_ERROR("Custom key: {0} does not exist", customKey);
				return false;
			}

			for (const auto& code : value->second)
			{
				bool isActive = false;
				switch (code.type)
				{
				case 0:		isActive = IsPressed(code.code.keyCode); break;
				case 1:		isActive = IsPressed(code.code.mouseCode); break;
				case 2:		isActive = IsPressed(code.code.gamepadButton); break;
				default:	LOG_WARN("CodeType was not detected!"); break;
				}
				
				if (isActive)
				{
					return true;
				}
			}
			
			return false;
		}
	}
}
