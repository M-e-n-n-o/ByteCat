#include "bcpch.h"
#include "byteCat/lua/LuaComponent.h"
#include "byteCat/lua/LuaScript.h"
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
		totalScripts--;

		if (totalScripts == 0)
		{
			lua_close(vm);
		}
	}

	void LuaComponent::onAttach()
	{
		attachFunc();
	}

	void LuaComponent::onUpdate()
	{
		updateFunc(Application::GetDelta());
	}

	void LuaComponent::onDetach()
	{
		detachFunc();
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
		LuaHelper::lua_function<void> attach(vm, "onAttach");
		attachFunc = attach;

		checkLua(luaL_dofile(vm, scriptName.c_str()));
		LuaHelper::lua_function<void> update(vm, "onUpdate");
		updateFunc = update;

		checkLua(luaL_dofile(vm, scriptName.c_str()));
		LuaHelper::lua_function<void> detach(vm, "onDetach");
		detachFunc = detach;
	}
}
