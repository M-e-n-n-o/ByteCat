#include "bcpch.h"
#include "byteCat/lua/LuaScript.h"

namespace BC
{
	LuaScript::LuaScript(std::string const& file)
	{
		if (totalScripts == 0)
		{
			luaState = luaL_newstate();
			luaL_openlibs(luaState);
		}

		luaFile = file;
		luaFile.insert(0, "res/");
		
		totalScripts++;
	}

	LuaScript::~LuaScript()
	{
		totalScripts--;
		
		if (totalScripts == 0)
		{
			lua_close(luaState);
		}
	}

	void LuaScript::callFunction(std::string const& name)
	{
		if (checkLua(luaL_dofile(luaState, luaFile.c_str())))
		{
			lua_getglobal(luaState, name.c_str());
			
			if (lua_isfunction(luaState, -1))
			{
				if (checkLua(lua_pcall(luaState, 0, 0, 0)))
				{
				}
			}
		}
	}

	bool LuaScript::checkLua(int LOG_ERROR) const
	{
		if (LOG_ERROR != LUA_OK)
		{
			LOG_ERROR("{0}", lua_tostring(luaState, -1));
			return false;
		}

		return true;
	}
}
