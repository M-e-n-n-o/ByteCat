#pragma once

#include <map>
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

		bool isSetInit = false;
		bool isGetInit = false;
		
		std::map<const char*, std::function<void()>> setFunctions;
		std::map<const char*, std::function<void()>> getFunctions;
	
	public:
		LuaScript(lua_State* luaState, std::string const& fileName);

		// Returns a function pointer to the function in the lua script
		template<typename Ret>
		LuaAPI::lua_function<Ret> getFunction(std::string const& funcName);

		// Adds a new function into the lua script
		void linkFunction(std::string const& funcName, int (*func)(lua_State*));

		// Adds a new 'Get' into the lua script which can be called by "Get({getName})"
		// ! Do not forget to pop the values which you take of the lua stack !
		void addGet(const char* getName, const std::function<void()>& func);

		// Adds a new 'Set' into the lua script which can be called by "Set({setName})"
		// ! Do not forget to pop the values which you take of the lua stack !
		void addSet(const char* setName, const std::function<void()>& func);

		// Call this function every frame to update the Get and Set functions for the script
		void update();

	private:
		bool checkLua(int error) const;
	};

	
	template <typename Ret>
	LuaAPI::lua_function<Ret> LuaScript::getFunction(std::string const& funcName)
	{
		checkLua(luaL_loadfile(vm, scriptName.c_str()));
		return LuaAPI::lua_function<Ret>(vm, funcName);
	}
}
