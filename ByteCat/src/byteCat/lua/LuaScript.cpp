#include "bcpch.h"
#include "byteCat/lua/LuaScript.h"
#include "byteCat/lua/LuaAPI.h"

namespace BC
{
	LuaScript::LuaScript(lua_State* luaState, std::string const& fileName): vm(luaState), scriptName(fileName)
	{
		// Link lua libraries
		luaL_requiref(vm, LUA_TABLIBNAME, luaopen_table, 1);
		lua_pop(vm, 1);
		luaL_requiref(vm, LUA_STRLIBNAME, luaopen_string, 1);
		lua_pop(vm, 1);
		luaL_requiref(vm, LUA_MATHLIBNAME, luaopen_math, 1);
		lua_pop(vm, 1);
		luaL_requiref(vm, LUA_LOADLIBNAME, luaopen_package, 1);
		lua_pop(vm, 1);
		luaL_requiref(vm, "_G", luaopen_base, 1);
		lua_pop(vm, 1);

		// Link standard ByteCat functions
		linkFunction("LOG_INFO", LuaAPI::LogInfo);
		linkFunction("LOG_ERROR", LuaAPI::LogError);

		luaL_dostring(vm, "package.path = '?.lua;res/?.lua;'");
		
		checkLua(luaL_dofile(vm, scriptName.c_str()));
	}

	void LuaScript::linkFunction(std::string const& funcName, int (*func)(lua_State*))
	{
		lua_register(vm, funcName.c_str(), func);
	}

	void LuaScript::addGet(const char* getName, const std::function<void()>& func)
	{
		if (!isGetInit)
		{
			linkFunction("Get", LuaAPI::Get);			
			isGetInit = true;
		}

		getFunctions.emplace(getName, func);
	}

	void LuaScript::addSet(const char* setName, const std::function<void()>& func)
	{
		if (!isSetInit)
		{
			linkFunction("Set", LuaAPI::Set);
			isSetInit = true;
		}

		setFunctions.emplace(setName, func);
	}

	void LuaScript::update()
	{
		LuaAPI::SetGetFunctions(getFunctions);
		LuaAPI::SetSetFunctions(setFunctions);
	}

	bool LuaScript::checkLua(int error) const
	{
		if (error != LUA_OK)
		{
			LOG_ERROR("Lua script \"{0}\": {1}", scriptName, lua_tostring(vm, -1));
			return false;
		}

		return true;
	}
}
