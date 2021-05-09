#pragma once

#include <iostream>

#ifdef BC_PLATFORM_WINDOWS
	#ifdef BC_BUILD_DLL
		#define BYTECAT_API __declspec(dllexport)
		#define BC_CORE_ACCESS
	#else
		#define BYTECAT_API __declspec(dllimport)
		#define BC_CLIENT_ACCESS
	#endif
#elif BC_PLATFORM_LINUX
	#ifdef BC_BUILD_DLL
		#define BYTECAT_API __attribute__((visibility("default")))
		#define BC_CORE_ACCESS
	#else
		#define BYTECAT_API
		#define BC_CLIENT_ACCESS
	#endif
#else
	#define BC_PLATFORM_NONE
	#error ByteCat does not support your platform right now :(
#endif


#ifdef BC_DEBUG
	#define BC_ENABLE_LOG

	#ifdef BC_PLATFORM_WINDOWS
		#define BC_DEBUG_BREAK __debugbreak()
	#elif BC_PLATFORM_LINUX
		#include <signal.h>
		#define BC_DEBUG_BREAK raise(SIGTRAP)
	#else
		#error "Platform does not support debugbreak yet!"
	#endif

#else
	#define BC_DEBUG_BREAK
#endif


#define BIT(x) (1 << x)

int main(int argc, char** argv);