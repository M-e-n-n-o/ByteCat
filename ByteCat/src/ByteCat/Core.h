#pragma once

#include <iostream>

#ifdef BC_PLATFORM_WINDOWS
	#ifdef BC_CORE
		#define BC_CORE_ACCESS
	#else
		#define BC_CLIENT_ACCESS
	#endif
#elif BC_PLATFORM_LINUX
	#ifdef BC_CORE
		#define  __attribute__((visibility("default")))
		#define BC_CORE_ACCESS
	#else
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

#elif BC_RELEASE
	#define BC_ENABLE_LOG
	#define BC_DEBUG_BREAK
#elif BC_DIST
	#define BC_DEBUG_BREAK
#endif


#define BIT(x) (1 << x)

#define BC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

int main(int argc, char** argv);