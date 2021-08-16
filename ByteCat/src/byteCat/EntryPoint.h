#pragma once

#include "byteCat/app/Application.h"

// This is defined on the users side
extern BC::Application* BC::CreateApplication();


#include "lua/src/lua.hpp"


// The start of the whole application
int main(int argc, char** argv)
{
	// BC::Log::Init();
	//
	// auto app = BC::CreateApplication();
	// app->start();
	//
	// delete app;
	//

	std::string cmd = "a = 5 + 5";

	lua_State* l = luaL_newstate();
	
	int r = luaL_dostring(l, cmd.c_str());

	if (r == LUA_OK)
	{
		lua_getglobal(l, "a");
		if (lua_isnumber(l, -1))
		{
			float a = (float)lua_tonumber(l, -1);
			std::cout << a << std::endl;
		}
	}
	else
	{
		std::string errormsg = lua_tostring(l, -1);
		std::cout << errormsg << std::endl;
	}

	lua_close(l);
}