#pragma once
#include <memory>
#include "byteCat/ecs/EcsCoordinator.h"
#include "byteCat/ecs/systems/CameraSystem.h"

namespace BC
{
	namespace Ecs
	{
		/**
		 * @brief
		 * Use this class as a manager of the whole entity system.
		 * This class will also create a EcsCoordinator which you can use
		 * to add entities, components and systems to your scene.
		 */
		class Scene
		{
		private:
			std::string m_name;
			std::shared_ptr<EcsCoordinator> m_ecsCoordinator;

			std::shared_ptr<CameraSystem> m_cameraSystem;

		public:
			Scene(const std::string& name);

			void onUpdate();

			std::string& getName() { return m_name; }
			std::shared_ptr<EcsCoordinator> getEcsCoordinator() const { return m_ecsCoordinator; }
		};
	}
}
