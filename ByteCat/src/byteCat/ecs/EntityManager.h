#pragma once
#include <bitset>
#include <queue>
#include "byteCat/ecs/Entity.h"

namespace BC
{	
	class EntityManager
	{
	private:
		std::queue<Entity> m_entities;
		std::array<Signature, MAX_ENTITIES> m_signatures;

		uint32_t m_entityCount = 0;
	
	public:
		EntityManager();

		Entity& createEntity();
		void destroyEntity(const Entity& entity);

		void setSignature(const Entity& entity, Signature signature);
		Signature& getSignature(const Entity& entity);
	};
}
