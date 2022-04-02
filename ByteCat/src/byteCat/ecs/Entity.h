#pragma once
#include <bitset>

namespace BC
{
	using Entity = std::uint32_t;
	const Entity MAX_ENTITIES = 10000;
	
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 32;

	using Dependencies = std::bitset<MAX_COMPONENTS>;
	
	#define TYPE_NAME(name) static const char* GetTypeName() { return (name); }
	
	struct Component
	{
		virtual ~Component() = default;
	};
}
