#pragma once

#include <string>
#include "byteCat/lua/LuaFunction.h"

namespace BC
{
	class LuaScript
	{
	private:
		lua_State* vm;
		std::string scriptName;

	public:
		LuaScript(lua_State* luaState, std::string const& fileName);

		template<typename Ret>
		LuaAPI::lua_function<Ret> getFunction(std::string const& funcName);

		void linkFunction(std::string const& funcName, int (*func)(lua_State*));

		void linkStandardFunctions();

		void addGetFunction(const char* getName, const std::function<void()>& func);

		void addSetFunction(const char* setName, const std::function<void()>& func);

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
