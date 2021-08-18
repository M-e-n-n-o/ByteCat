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
		linkFunction("LogInfo", LuaAPI::LogInfo);
		linkFunction("LogError", LuaAPI::LogError);
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
