#pragma once

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX) || defined(BC_PLATFORM_ANDROID)
	#ifdef BC_CORE
		#define BC_CORE_ACCESS
	#else
		#define BC_CLIENT_ACCESS
	#endif
#else
	#define BC_PLATFORM_NONE
	#error ByteCat does not support your platform right now, or your platform was not specified :(
#endif

#ifdef BC_DEBUG
	#define BC_ENABLE_LOG

	#ifdef BC_PLATFORM_WINDOWS
		#define BC_DEBUG_BREAK __debugbreak()
	#elif BC_PLATFORM_LINUX
		#include <signal.h>
		#define BC_DEBUG_BREAK raise(SIGTRAP)
	#elif BC_PLATFORM_ANDROID
		#define BC_DEBUG_BREAK  
	#else
		#error "Platform does not support debugbreak yet!"
	#endif

#elif BC_RELEASE
	#define BC_ENABLE_LOG
	#define BC_DEBUG_BREAK
#elif BC_DIST
	#define BC_DEBUG_BREAK
#endif

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
	#define BC_PLATFORM_PC
#elif defined(BC_PLATFORM_ANDROID)
	#define BC_PLATFORM_MOBILE
#endif