#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "byteCat/lua/LuaScript.h"

namespace BC
{
	class LuaComponent : public ObjectComponent
	{
	private:
		lua_State* vm;
		LuaScript* script;

		std::unique_ptr<LuaAPI::lua_function<void>> attachFunc;
		std::unique_ptr<LuaAPI::lua_function<void>> updateFunc;
		std::unique_ptr<LuaAPI::lua_function<void>> detachFunc;

		std::function<void()> attachCallback;
		std::function<void(double)> updateCallback;
		std::function<void()> detachCallback;
	
	public:
		LuaComponent(std::string const& scriptName);
		~LuaComponent() override;
		
		void onAttach() override;
		void onUpdate() override;
		void onDetach() override;
	};
}
