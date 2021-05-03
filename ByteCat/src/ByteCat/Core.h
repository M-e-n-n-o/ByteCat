#pragma once

#ifdef BC_PLATFORM_WINDOWS
	#ifdef BC_BUILD_DLL
		#define BYTECAT_API __declspec(dllexport)
		#define BC_CORE_ACCESS
	#else
		#define BYTECAT_API __declspec(dllimport)
		#define BC_CLIENT_ACCESS
	#endif
#else
	#error ByteCat only supports Windows!
#endif

#ifdef BC_DEBUG
	#define BC_ENABLE_LOG
#endif