#pragma once

#include "byteCat/entity-system/GameObject.h"
#include "byteCat/lua/LuaScript.h"

namespace BC
{
	/*
	 * Class LuaComponent:
	 *		This component holds a lua script which gets called when this component gets called.
	 */
	class LuaComponent : public ObjectComponent
	{
	private:
		lua_State* vm;
		LuaScript* script;

		std::function<void()> attachCallback;
		std::function<void(double)> updateCallback;
		std::function<void()> detachCallback;
	
	public:
		LuaComponent(std::string const& scriptName);
		~LuaComponent() override;
		
		void onAttach() override;
		void onUpdate() override;
		void onDetach() override;

	private:
		void linkGetSetFunctions(std::string const& scriptName);
	};
}
