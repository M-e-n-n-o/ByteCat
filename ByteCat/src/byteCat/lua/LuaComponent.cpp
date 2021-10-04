#include "bcpch.h"
#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 348
#include <magic_enum.hpp>
#include "byteCat/input/Input.h"
#include "byteCat/lua/LuaComponent.h"
#include "byteCat/app/Application.h"

namespace BC
{	
	static void PushTableComponent(lua_State* vm, const char* key, float value)
	{
		lua_pushstring(vm, key);
		lua_pushnumber(vm, value);
		lua_settable(vm, -3);
	}

	static float GetTableComponent(lua_State* vm, const char* key)
	{
		lua_pushstring(vm, key);
		lua_gettable(vm, -2);
		float value = (float)lua_tonumber(vm, -1);
		lua_pop(vm, 1);
		return value;
	}

	static int IsKeyPressed(lua_State* vm)
	{
		const char* keyString = lua_tostring(vm, 1);
		lua_settop(vm, 0);

		auto keyEnum = magic_enum::enum_cast<KeyCode>(keyString);
		if (keyEnum.has_value())
		{
			if (Input::IsKeyPressed(keyEnum.value()))
			{
				lua_pushboolean(vm, 1);
			}
			else
			{
				lua_pushboolean(vm, 0);
			}
		}
		else
		{
			LOG_WARN("Requested keycode \"{1}\", from a lua file, was not found", keyString);
			lua_pushboolean(vm, 0);
		}

		return 1;
	}

	static int IsMouseButtonPressed(lua_State* vm)
	{
		const char* mouseString = lua_tostring(vm, -1);
		lua_settop(vm, 0);

		auto mouseEnum = magic_enum::enum_cast<MouseCode>(mouseString);
		if (mouseEnum.has_value())
		{
			if (Input::IsMouseButtonPressed(mouseEnum.value()))
			{
				lua_pushboolean(vm, 1);
			}
			else
			{
				lua_pushboolean(vm, 0);
			}
		}
		else
		{
			LOG_WARN("Requested mousecode \"{1}\", from a lua file, was not found", mouseString);
			lua_pushboolean(vm, 0);
		}

		return 1;
	}
	
	LuaComponent::LuaComponent(std::string const& scriptName)
	{		
		name = scriptName;

		std::string file = scriptName; file.insert(0, BC_RES_FOLDER); file.append(".lua");
		
		vm = luaL_newstate();
		script = new LuaScript(vm, file);
		
		// Link objectComponent functions
		auto attachFunc = script->getFunction<void>("onAttach");
		if (attachFunc != nullptr)
		{
			attachCallback = *attachFunc;
		} else { LOG_INFO("OnAttach function not found in a lua script \"{0}\"", scriptName); }

		auto updateFunc = script->getFunction<void>("onUpdate");
		if (updateFunc != nullptr)
		{
			updateCallback = *updateFunc;
			updateFunc->cleanUp();
		} else { LOG_INFO("onUpdate function not found in a lua script \"{0}\"", scriptName); }

		auto detachFunc = script->getFunction<void>("onDetach");
		if (detachFunc != nullptr)
		{
			detachCallback = *detachFunc;
		} else { LOG_INFO("onDetach function not found in a lua script \"{0}\"", scriptName); }

		linkGetSetFunctions(scriptName);
		script->linkFunction("IsKeyPressed", IsKeyPressed);
		script->linkFunction("IsMouseButtonPressed", IsMouseButtonPressed);
	}

	LuaComponent::~LuaComponent()
	{		
		delete script;
		lua_close(vm);
	}

	void LuaComponent::onAttach()
	{
		if (attachCallback != nullptr)
		{
			attachCallback();
		}
	}

	void LuaComponent::onUpdate()
	{	
		// TODO Make this section thread safe (this may not be interrupted)
		if (updateCallback != nullptr)
		{
			script->update();
			updateCallback(Application::GetDelta());
		}
	}

	void LuaComponent::onDetach()
	{
		if (detachCallback != nullptr)
		{
			detachCallback();
		}
	}

	void LuaComponent::linkGetSetFunctions(std::string const& scriptName)
	{
		// Link Get variables
		script->addGet("position", [=]()
			{
				lua_pop(vm, 1);
				glm::vec3& pos = gameObject->transform.position;

				lua_newtable(vm);
				PushTableComponent(vm, "x", pos.x);
				PushTableComponent(vm, "y", pos.y);
				PushTableComponent(vm, "z", pos.z);
			});

		script->addGet("rotation", [=]()
			{
				lua_pop(vm, 1);
				glm::vec3& rot = gameObject->transform.rotation;

				lua_newtable(vm);
				PushTableComponent(vm, "x", rot.x);
				PushTableComponent(vm, "y", rot.y);
				PushTableComponent(vm, "z", rot.z);
			});

		script->addGet("scale", [=]()
			{
				lua_pop(vm, 1);
				glm::vec3& scale = gameObject->transform.scale;

				lua_newtable(vm);
				PushTableComponent(vm, "x", scale.x);
				PushTableComponent(vm, "y", scale.y);
				PushTableComponent(vm, "z", scale.z);
			});
		

		// Link Set variables
		script->addSet("position", [=]()
			{
				if (!lua_istable(vm, 2))
				{
					LOG_WARN("LuaFile {0}, Did not pass a table into the Set position function", scriptName);
					return;
				}

				float x = GetTableComponent(vm, "x");
				float y = GetTableComponent(vm, "y");
				float z = GetTableComponent(vm, "z");

				gameObject->transform.position = { x, y, z };
			});

		script->addSet("rotation", [=]()
			{
				if (!lua_istable(vm, 2))
				{
					LOG_WARN("LuaFile {0}, Did not pass a table into the Set rotation function", scriptName);
					return;
				}

				float x = GetTableComponent(vm, "x");
				float y = GetTableComponent(vm, "y");
				float z = GetTableComponent(vm, "z");

				gameObject->transform.rotation = { x, y, z };
			});

		script->addSet("scale", [=]()
			{
				if (!lua_istable(vm, 2))
				{
					LOG_WARN("LuaFile {0}, Did not pass a table into the Set scale function", scriptName);
					return;
				}

				float x = GetTableComponent(vm, "x");
				float y = GetTableComponent(vm, "y");
				float z = GetTableComponent(vm, "z");

				gameObject->transform.scale = { x, y, z };
			});
	}
}
