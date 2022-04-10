#pragma once
#include <glm/glm.hpp>

namespace BC
{
	namespace Utils
	{
		class Math
		{
		public:
			static glm::mat4 CreateModelMatrix(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);

			static glm::mat4 CreateViewMatrix(const glm::vec3& pos, const glm::vec3& rot);

			static float RandomBetween(float smallNumber, float bigNumber);
		};
	}
}
