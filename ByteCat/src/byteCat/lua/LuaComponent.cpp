#include "bcpch.h"
#include "byteCat/lua/LuaComponent.h"
#include "byteCat/app/Application.h"

namespace BC
{	
	LuaComponent::LuaComponent(std::string const& fileName)
	{	
		if (totalScripts == 0)
		{
			vm = luaL_newstate();
			luaL_openlibs(vm);
		}

		scriptName = fileName;
		scriptName.insert(0, "res/");

		totalScripts++;

		addFunctions();
	}

	LuaComponent::~LuaComponent()
	{
		attachFunc->cleanUp();
		updateFunc->cleanUp();
		detachFunc->cleanUp();
		
		totalScripts--;

		if (totalScripts == 0)
		{
			lua_close(vm);
		}
	}

	void LuaComponent::onAttach()
	{
		attachCallback();
	}

	void LuaComponent::onUpdate()
	{
		updateCallback(scriptName);
	}

	void LuaComponent::onDetach()
	{
		detachCallback();
	}

	bool LuaComponent::checkLua(int error) const
	{
		if (error != LUA_OK)
		{
			LOG_ERROR("{0}", lua_tostring(vm, -1));
			return false;
		}

		return true;
	}

	void LuaComponent::addFunctions()
	{
		checkLua(luaL_dofile(vm, scriptName.c_str()));
		attachFunc = std::make_unique<LuaHelper::lua_function<void>>(vm, "onAttach");
		attachCallback = *attachFunc;

		checkLua(luaL_dofile(vm, scriptName.c_str()));
		updateFunc = std::make_unique<LuaHelper::lua_function<void>>(vm, "onUpdate");
		updateCallback = *updateFunc;

		checkLua(luaL_dofile(vm, scriptName.c_str()));
		detachFunc = std::make_unique<LuaHelper::lua_function<void>>(vm, "onDetach");
		detachCallback = *detachFunc;
	}
}
