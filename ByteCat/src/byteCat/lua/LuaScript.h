#pragma once

#include <lua.hpp>

namespace BC
{	
	/*
	 * Class LuaScript:
	 *		This class represents a lua script in a ByteCat application
	 */
	class LuaScript
	{
	private:
		inline static int totalScripts = 0;
		inline static lua_State* luaState;

		std::string luaFile;
	
	public:
		LuaScript(std::string const& file);
		~LuaScript();
		
		void callFunction(std::string const& name);
	private:
		bool checkLua(int error) const;
	};
}
