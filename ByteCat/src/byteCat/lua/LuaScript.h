#pragma once

#include <string>
#include "byteCat/lua/LuaFunction.h"

namespace BC
{
	/*
	 * Class LuaScript:
	 *		This class represents a lua script in the ByteCat engine.
	 */
	class LuaScript
	{
	private:
		lua_State* vm;
		std::string scriptName;

	public:
		LuaScript(lua_State* luaState, std::string const& fileName);

		// Returns a function pointer to the function in the lua script
		template<typename Ret>
		LuaAPI::lua_function<Ret> getFunction(std::string const& funcName);

		// Adds a new function into the lua script
		void linkFunction(std::string const& funcName, int (*func)(lua_State*));

		// Adds some standard lua libraries and ByteCat functions into the lua script
		void linkStandardFunctions();

		// Adds a new 'Get' into the lua script which can be called by "Get({getName})"
		void addGet(const char* getName, const std::function<void()>& func);

		// Adds a new 'Set' into the lua script which can be called by "Set({setName})"
		// ! Do not forget to pop the values which you take of the lua stack !
		void addSet(const char* setName, const std::function<void()>& func);

	private:
		bool checkLua(int error) const;
	};

	
	template <typename Ret>
	LuaAPI::lua_function<Ret> LuaScript::getFunction(std::string const& funcName)
	{
		checkLua(luaL_dofile(vm, scriptName.c_str()));
		return LuaAPI::lua_function<Ret>(vm, funcName);
	}
}
