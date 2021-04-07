#pragma once

#ifdef BC_PLATFORM_WINDOWS
	#ifdef BC_BUILD_DLL
		#define BYTECAT_API __declspec(dllexport)
	#else
		#define BYTECAT_API __declspec(dllimport)
	#endif
#else
	#error ByteCat only supports Windows!
#endif
