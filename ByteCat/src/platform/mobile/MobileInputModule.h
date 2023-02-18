#pragma once
#ifdef BC_PLATFORM_MOBILE

#include <glfm.h>

namespace BC
{
	namespace Inputs
	{
		enum class MobileSensorType
		{
			Accelerometer,
			Magnetometer,
			Gyroscope,
			RotationMatrix
		};

		class MobileInputModule
		{
		public:
			virtual ~MobileInputModule() = default;
		};
	}
}

#endif