#include "bcpch.h"
#include "byteCat/lua/LuaScript.h"
#include "byteCat/lua/LuaInterface.h"

namespace BC
{
	LuaScript::LuaScript(lua_State* luaState, std::string const& fileName): vm(luaState), scriptName(fileName)
	{
		checkLua(luaL_dofile(vm, scriptName.c_str()));
	}

	void LuaScript::linkFunction(std::string const& funcName, int (*func)(lua_State*))
	{
		lua_register(vm, funcName.c_str(), func);
	}

	void LuaScript::linkStandardFunctions()
	{
		// Link lua libraries
		luaL_requiref(vm, LUA_TABLIBNAME, luaopen_table, 1);
		lua_pop(vm, 1);
		luaL_requiref(vm, LUA_STRLIBNAME, luaopen_string, 1);
		lua_pop(vm, 1);
		luaL_requiref(vm, LUA_MATHLIBNAME, luaopen_math, 1);
		lua_pop(vm, 1);

		// Link ByteCat functions
		linkFunction("LOG_INFO", LuaAPI::LogInfo);
		linkFunction("LOG_ERROR", LuaAPI::LogError);
	}

	void LuaScript::addGet(const char* getName, const std::function<void()>& func)
	{
		if (static bool hasFunction = false; !hasFunction)
		{
			linkFunction("Get", LuaAPI::Get);
			hasFunction = true;
		}
		
		LuaAPI::AddGet(getName, func);
	}

	void LuaScript::addSet(const char* setName, const std::function<void()>& func)
	{
		if (static bool hasFunction = false; !hasFunction)
		{
			linkFunction("Set", LuaAPI::Set);
			hasFunction = true;
		}
		
		LuaAPI::AddSet(setName, func);
	}

	bool LuaScript::checkLua(int error) const
	{
		if (error != LUA_OK)
		{
			LOG_ERROR("{0}", lua_tostring(vm, -1));
			return false;
		}

		return true;
	}
}
