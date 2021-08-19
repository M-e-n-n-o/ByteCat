#include "bcpch.h"
#include "byteCat/lua/LuaComponent.h"
#include "byteCat/app/Application.h"

namespace BC
{	
	LuaComponent::LuaComponent(std::string const& scriptName)
	{
		vm = luaL_newstate();
		script = new LuaScript(vm, scriptName);
		script->linkStandardFunctions();

		attachFunc = std::make_unique<LuaAPI::lua_function<void>>(script->getFunction<void>("onAttach"));
		attachCallback = *attachFunc;

		updateFunc = std::make_unique<LuaAPI::lua_function<void>>(script->getFunction<void>("onUpdate"));
		updateCallback = *updateFunc;

		detachFunc = std::make_unique<LuaAPI::lua_function<void>>(script->getFunction<void>("onUpdate"));
		detachCallback = *detachFunc;
	}

	LuaComponent::~LuaComponent()
	{		
		attachFunc->cleanUp();
		updateFunc->cleanUp();
		detachFunc->cleanUp();
		
		delete script;
		
		lua_close(vm);
	}

	void LuaComponent::onAttach()
	{
		attachCallback();
	}

	void LuaComponent::onUpdate()
	{
		updateCallback(Application::GetDelta());
	}

	void LuaComponent::onDetach()
	{
		detachCallback();
	}
}
