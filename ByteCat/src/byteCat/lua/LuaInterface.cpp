#include "bcpch.h"
#include "byteCat/lua/LuaInterface.h"
#include <map>

namespace BC
{
	namespace LuaAPI
	{
		// Get
		static std::map<const char*, std::function<void()>> GetFunctions;

		int Get(lua_State* vm)
		{
			const char* msg = lua_tostring(vm, 1);
			lua_pop(vm, 1);

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

		void AddGet(const char* getName, const std::function<void()>& func)
		{
			GetFunctions.emplace(getName, func);
		}


		// Set
		static std::map<const char*, std::function<void()>> SetFunctions;
		
		int Set(lua_State* vm)
		{
			const char* msg = lua_tostring(vm, 1);
			lua_pop(vm, 1);

			for (auto& function : SetFunctions)
			{
				if (!strcmp(function.first, msg))
				{
					function.second();
					lua_pop(vm, 1);
					
					return 0;
				}
			}

			LOG_WARN("Requested Set \"{0}\" from a luascript could not be found", msg);
			
			return 0;
		}

		void AddSet(const char* setName, const std::function<void()>& func)
		{
			SetFunctions.emplace(setName, func);
		}
	}
}
