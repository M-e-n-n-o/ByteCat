#pragma once
#include "byteCat/ecs/Entity.h"

namespace BC
{
	namespace Ecs
	{
		class EcsCoordinator;

		class Behaviour
		{
		private:
			friend class EntityManager;

		protected:
			EcsCoordinator* m_coordinator;
			Entity m_entity = -1;

			bool m_enabled = true;

		public:
			virtual ~Behaviour() = default;

			virtual void onAttach() {}
			virtual void onUpdate() {}
			virtual void onDetach() {}

			void setEnabled(bool enabled) { m_enabled = enabled; }
		};
	}
}
