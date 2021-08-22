#pragma once

#include <lua.hpp>
#include <map>
#include "byteCat/Log.h"

namespace BC
{
	namespace LuaAPI
	{		
		inline int LogInfo(lua_State* vm)
		{
			const char* msg = lua_tostring(vm, 1);
			lua_pop(vm, 1);
			LOG_INFO("LuaScript: {0}", msg);
			return 0;
		}

		inline int LogError(lua_State* vm)
		{
			const char* msg = lua_tostring(vm, 1);
			lua_pop(vm, 1);
			LOG_ERROR("LuaScript: {0}", msg);
			return 0;
		}

		// This function is used for a lua script to execute the Get command
		int Get(lua_State* vm);
		// Call this function to set the different Get functions for the Get function
		void SetGetFunctions(std::map<const char*, std::function<void()>>& functions);

		// This function is used for a lua script to execute the Set command
		int Set(lua_State* vm);
		// Call this function to set the different Get functions for the Get function
		void SetSetFunctions(std::map<const char*, std::function<void()>>& functions);
	}
}
