#pragma once

#include <lua.hpp>

namespace BC
{
	// Thanks for the inspiration for this code: reko_t
	
	namespace LuaAPI
	{		
		void LOG(std::string string);
		
		// we overload push_value instead of specializing
		// because this way we can also push values that
		// are implicitly convertible to one of the types

		inline void push_value(lua_State* vm, lua_Integer n)
		{
			lua_pushinteger(vm, n);
		}

		inline void push_value(lua_State* vm, lua_Number n)
		{
			lua_pushnumber(vm, n);
		}

		inline void push_value(lua_State* vm, bool b)
		{
			lua_pushboolean(vm, b);
		}

		inline void push_value(lua_State* vm, const std::string& s)
		{
			lua_pushstring(vm, s.c_str());
		}

		// other overloads, for stuff like userdata or C functions

		// for extracting return values, we specialize a simple struct
		// as overloading on return type does not work, and we only need
		// to support a specific set of return types, as the return type
		// of a function is always specified explicitly

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

		// other specializations, for stuff like userdata or C function

		// the base function wrapper class
		class lua_function_base
		{
		public:
			bool isFound = true;
			
			lua_function_base(lua_State* vm, const std::string& func)
				: m_vm(vm)
			{
				lua_getglobal(vm, func.c_str());
				
				// ensure it's a function
				if (!lua_isfunction(m_vm, -1)) {
					lua_pop(m_vm, 1);
					LOG(func + " function not found in a lua script");
					isFound = false;
					return;
				}
				
				// store it in registry for later use
				m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
			}

			lua_function_base(const lua_function_base& func)
				: m_vm(func.m_vm)
			{
				// copy the registry reference
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);
				m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
			}

			~lua_function_base()
			{
				//cleanUp();
			}

			void cleanUp()
			{
				// delete the reference from registry
				luaL_unref(m_vm, LUA_REGISTRYINDEX, m_func);
			}

			lua_function_base& operator=(const lua_function_base& func)
			{
				if (this != &func) {
					m_vm = func.m_vm;
					lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);
					m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
				}
				return *this;
			}
		protected:
			// the virtual machine and the registry reference to the function
			lua_State* m_vm;
			int m_func;

			// call the function, throws an exception on error
			void call(int args, int results)
			{
				int status = lua_pcall(m_vm, args, results, 0);
				if (status != 0) {
					// call failed; throw an exception
					std::string error = lua_tostring(m_vm, -1);
					lua_pop(m_vm, 1);
					LOG(error);
				}
			}
		};

		// the function wrapper class
		template <typename Ret>
		class lua_function : public lua_function_base
		{
		public:
			lua_function(lua_State* vm, const std::string& func)
				: lua_function_base(vm, func)
			{
			}

			Ret operator()()
			{
				// push the function from the registry
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				// call the function on top of the stack (throws exception on error)
				call(0, 1);
				// return the value
				return value_extractor<Ret>::get(m_vm);
			}

			template <typename T1>
			Ret operator()(const T1& p1)
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				// push the argument and call with 1 arg
				push_value(m_vm, p1);
				call(1, 1);
				return value_extractor<Ret>::get(m_vm);
			}

			template <typename T1, typename T2>
			Ret operator()(const T1& p1, const T2& p2)
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				// push the arguments and call with 2 args
				push_value(m_vm, p1);
				push_value(m_vm, p2);
				call(2, 1);
				return value_extractor<Ret>::get(m_vm);
			}

			template <typename T1, typename T2, typename T3>
			Ret operator()(const T1& p1, const T2& p2, const T3& p3)
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				push_value(m_vm, p1);
				push_value(m_vm, p2);
				push_value(m_vm, p3);
				call(3, 1);
				return value_extractor<Ret>::get(m_vm);
			}
		};

		template <>
		class lua_function<void> : public lua_function_base
		{
		public:
			lua_function(lua_State* vm, const std::string& func)
				: lua_function_base(vm, func)
			{
			}

			void operator()()
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				call(0, 0);
			}

			template <typename T1>
			void operator()(const T1& p1)
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				push_value(m_vm, p1);
				call(1, 0);
			}

			template <typename T1, typename T2>
			void operator()(const T1& p1, const T2& p2)
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				push_value(m_vm, p1);
				push_value(m_vm, p2);
				call(2, 0);
			}

			template <typename T1, typename T2, typename T3>
			void operator()(const T1& p1, const T2& p2, const T3& p3)
			{
				lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
				push_value(m_vm, p1);
				push_value(m_vm, p2);
				push_value(m_vm, p3);
				call(3, 0);
			}
		};
	}
}
