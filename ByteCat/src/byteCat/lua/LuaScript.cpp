#include "bcpch.h"
#include "byteCat/lua/LuaScript.h"

namespace BC
{
	LuaScript::LuaScript(std::string const& file)
	{
		if (totalScripts == 0)
		{
			vm = luaL_newstate();
			luaL_openlibs(vm);
		}

		fileName = file;
		fileName.insert(0, "res/");

		totalScripts++;
	}

	LuaScript::~LuaScript()
	{
		totalScripts--;
		
		if (totalScripts == 0)
		{
			lua_close(vm);
		}
	}

	bool LuaScript::checkLua(int LOG_ERROR) const
	{
		if (LOG_ERROR != LUA_OK)
		{
			LOG_ERROR("{0}", lua_tostring(vm, -1));
			return false;
		}

		return true;
	}
}
