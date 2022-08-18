#ifdef BC_PLATFORM_MOBILE
#include "bcpch.h"

#include "byteCat/app/Time.h"

namespace BC
{
	namespace App
	{
		void Time::onUpdate()
		{
			s_deltaTime = 0.1;
		}
	}
}

#endif