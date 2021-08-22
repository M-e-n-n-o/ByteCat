#include "bcpch.h"
#include "byteCat/lua/LuaAPI.h"

namespace BC
{
	namespace LuaAPI
	{
		// Get
		static std::map<const char*, std::function<void()>> GetFunctions;

		int Get(lua_State* vm)
		{
			if (!lua_isstring(vm, 1))
			{
				LOG_WARN("First argument of Get function needs to be a string!");
				return 0;
			}
			
			const char* msg = lua_tostring(vm, 1);			
			
			for (auto& function : GetFunctions)
			{
				if (!strcmp(function.first, msg))
				{
					function.second();
					
					return 1;
				}
			}

			LOG_WARN("Requested Get \"{0}\" from a luascript could not be found", msg);

			return 0;
		}

		void SetGetFunctions(std::map<const char*, std::function<void()>>& functions)
		{
			GetFunctions = functions;
		}


		// Set
		static std::map<const char*, std::function<void()>> SetFunctions;
		
		int Set(lua_State* vm)
		{
			if (!lua_isstring(vm, 1))
			{
				LOG_WARN("First argument of Set function needs to be a string!");
				return 0;
			}
			
			const char* msg = lua_tostring(vm, 1);			
			
			for (auto& function : SetFunctions)
			{
				if (!strcmp(function.first, msg))
				{
					function.second();
					lua_settop(vm, 0);
					
					return 0;
				}
			}

			LOG_WARN("Requested Set \"{0}\" from a luascript could not be found", msg);
			
			return 0;
		}

		void SetSetFunctions(std::map<const char*, std::function<void()>>& functions)
		{
			SetFunctions = functions;
		}
	}
}
