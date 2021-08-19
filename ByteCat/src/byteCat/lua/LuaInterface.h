#pragma once

#include "byteCat/Log.h"
#include <lua.hpp>

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

		int Get(lua_State* vm);
		void AddGet(const char* getName, const std::function<void()>& func);

		int Set(lua_State* vm);
		void AddSet(const char* setName, const std::function<void()>& func);
	}
}
