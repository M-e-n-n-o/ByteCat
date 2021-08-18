#pragma once

#include "byteCat/lua/LuaHelper.h"
#include "byteCat/entity-system/GameObject.h"

namespace BC
{
	class LuaComponent : public ObjectComponent
	{
	private:
		inline static lua_State* vm;
		inline static int totalScripts = 0;

		std::string scriptName;

		std::function<void()> attachCallback;
		std::unique_ptr<LuaHelper::lua_function<void>> attachFunc;
		
		std::function<void(std::string)> updateCallback;
		std::unique_ptr<LuaHelper::lua_function<void>> updateFunc;
		
		std::function<void()> detachCallback;
		std::unique_ptr<LuaHelper::lua_function<void>> detachFunc;
	
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
