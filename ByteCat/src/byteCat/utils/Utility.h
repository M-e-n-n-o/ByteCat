#pragma once

namespace BC
{
	namespace Utils
	{
		class Utility
		{
		public:
			
#ifdef BC_PLATFORM_ANDROID
			// This will lock the application until the user has accepted or denied the request
			static void RequestPermissions(std::initializer_list<const char*> permissions);
#endif
		};
	}
}