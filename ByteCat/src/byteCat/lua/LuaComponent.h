#pragma once

#include <lua.hpp>
#include "byteCat/entity-system/GameObject.h"

namespace BC
{
	class LuaComponent : public ObjectComponent
	{
	private:
		inline static lua_State* vm;
		inline static int totalScripts = 0;

		std::string scriptName;

		std::function<void()> attachFunc;
		std::function<void(double)> updateFunc;
		std::function<void()> detachFunc;
	
	public:
		LuaComponent(std::string const& fileName);
		~LuaComponent() override;
		
		void onAttach() override;
		void onUpdate() override;
		void onDetach() override;

	private:
		bool checkLua(int error) const;
		void addFunctions();
	};
}
