#pragma once

#include <lua.hpp>
#include <map>

namespace BC
{
	// Helper functions
	template <typename T>
	struct value_extractor
	{
	};

	template <>
	struct value_extractor<lua_Integer>
	{
		static lua_Integer get(lua_State* vm)
		{
			lua_Integer val = lua_tointeger(vm, -1);
			lua_pop(vm, 1);
			return val;
		}
	};

	template <>
	struct value_extractor<lua_Number>
	{
		static lua_Number get(lua_State* vm)
		{
			lua_Number val = lua_tonumber(vm, -1);
			lua_pop(vm, 1);
			return val;
		}
	};

	template <>
	struct value_extractor<bool>
	{
		static bool get(lua_State* vm)
		{
			bool val = lua_toboolean(vm, -1);
			lua_pop(vm, 1);
			return val;
		}
	};

	template <>
	struct value_extractor<std::string>
	{
		static std::string get(lua_State* vm)
		{
			std::string val = lua_tostring(vm, -1);
			lua_pop(vm, 1);
			return val;
		}
	};

	// Lua functions
	class LuaFunctionBase
	{
	protected:
		lua_State* vm;
		int func;
	
	public:
		LuaFunctionBase(lua_State* vm, const std::string& func): vm(vm)
		{
			lua_getglobal(vm, func.c_str());

			if (!lua_isfunction(vm, -1)) {
				lua_pop(vm, 1);
				LOG_ERROR("{0}", lua_tostring(vm, -1));
			}

			this->func = luaL_ref(vm, LUA_REGISTRYINDEX);
		}

		LuaFunctionBase(const LuaFunctionBase& func): vm(func.vm)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func.func);
			this->func = luaL_ref(vm, LUA_REGISTRYINDEX);
		}

		~LuaFunctionBase()
		{
			luaL_unref(vm, LUA_REGISTRYINDEX, func);
		}

		LuaFunctionBase& operator=(const LuaFunctionBase& func)
		{
			if (this != &func) {
				vm = func.vm;
				lua_rawgeti(vm, LUA_REGISTRYINDEX, func.func);
				this->func = luaL_ref(vm, LUA_REGISTRYINDEX);
			}
			return *this;
		}

	protected:
		void call(int args, int results)
		{
			int status = lua_pcall(vm, args, results, 0);
			if (status != LUA_OK)
			{
				LOG_ERROR(lua_tostring(vm, -1));
				lua_pop(vm, -1);
			}
		}
	};

	template<typename T>
	class LuaFunction : public LuaFunctionBase
	{
	public:
		LuaFunction(lua_State* vm, const std::string& func): LuaFunctionBase(vm, func) {}
		
		T operator()()
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			call(0, 1);
			return value_extractor<T>::get(vm);
		}

		template <typename T1>
		T operator()(const T1& p1)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			push_value(vm, p1);
			call(1, 1);
			return value_extractor<T>::get(vm);
		}

		template <typename T1, typename T2>
		T operator()(const T1& p1, const T2& p2)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			push_value(vm, p1);
			push_value(vm, p2);
			call(2, 1);
			return value_extractor<T>::get(vm);
		}

		template <typename T1, typename T2, typename T3>
		T operator()(const T1& p1, const T2& p2, const T3& p3)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			push_value(vm, p1);
			push_value(vm, p2);
			push_value(vm, p3);
			call(3, 1);
			return value_extractor<T>::get(vm);
		}
	};

	template<>
	class LuaFunction<void> : public LuaFunctionBase
	{
	public:
		LuaFunction(lua_State* vm, const std::string& func) : LuaFunctionBase(vm, func) {}
		
		void operator()()
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			call(0, 0);
		}

		template <typename T1>
		void operator()(const T1& p1)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			push_value(vm, p1);
			call(1, 0);
		}

		template <typename T1, typename T2>
		void operator()(const T1& p1, const T2& p2)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			push_value(vm, p1);
			push_value(vm, p2);
			call(2, 0);
		}

		template <typename T1, typename T2, typename T3>
		void operator()(const T1& p1, const T2& p2, const T3& p3)
		{
			lua_rawgeti(vm, LUA_REGISTRYINDEX, func);
			push_value(vm, p1);
			push_value(vm, p2);
			push_value(vm, p3);
			call(3, 0);
		}
	};


	// --------------------------------------------------------------------------------
	// -------------------------------- LuaScript -------------------------------------
	// --------------------------------------------------------------------------------
	

	/*
	 * Class LuaScript:
	 *		This class represents a lua script in a ByteCat application
	 */
	class LuaScript
	{
	private:
		inline static int totalScripts = 0;
		inline static lua_State* vm;
		
		std::string fileName;
	
	public:
		LuaScript(std::string const& file);
		~LuaScript();

		template<typename T>
		std::function<T()> addFunction(std::string const& name)
		{
			checkLua(luaL_dofile(vm, fileName.c_str()));
			return LuaFunction<T>(vm, name);
		}
		
	private:
		bool checkLua(int error) const;
	};
}