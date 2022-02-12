#pragma once
#include <bitset>

namespace BC
{
	using Entity = std::uint32_t;
	const Entity MAX_ENTITIES = 10000;
	
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;


	
	#define TYPE_NAME(name) static const char* getTypeName() { return (name); }
	
	struct Component
	{
		virtual ~Component() = default;
	};
}
