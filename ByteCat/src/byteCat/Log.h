#pragma once

#include "byteCat/Platform.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef BC_PLATFORM_PC
	#include <iostream>
#elif defined(BC_PLATFORM_ANDROID)
	#include <android/log.h>
#endif

// Logging
#ifdef BC_ENABLE_LOG

	#ifdef BC_PLATFORM_PC
		#define LOG_TEXT_LONG(x)			std::cout << (x) << std::endl
	#elif defined(BC_PLATFORM_ANDROID)
		#define LOG_TEXT_LONG(x)			__android_log_print(ANDROID_LOG_VERBOSE, "", x)
	#endif

	// Core log/assert macros
	#ifdef BC_CORE_ACCESS
		#ifdef BC_PLATFORM_PC
			#define LOG_ESSENTIAL(x)		::BC::Log::GetCoreLogger()->info(x)
			#define LOG_INFO(...)			::BC::Log::GetCoreLogger()->info(__VA_ARGS__)
			#define LOG_WARN(...)			::BC::Log::GetCoreLogger()->warn(__VA_ARGS__)
			#define LOG_ERROR(...)			::BC::Log::GetCoreLogger()->error(__VA_ARGS__)
			#define LOG_CRITICAL(x)			::BC::Log::GetCoreLogger()->critical(x)
			#define LOG_ASSERT(x, ...)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BC_DEBUG_BREAK; } }
		#elif defined(BC_PLATFORM_ANDROID)
			#define LOG_ESSENTIAL(x)		__android_log_print(ANDROID_LOG_VERBOSE, "ByteCat", x)
			#define LOG_INFO(...)			__android_log_print(ANDROID_LOG_INFO, "ByteCat", __VA_ARGS__)
			#define LOG_WARN(...)			__android_log_print(ANDROID_LOG_WARN, "ByteCat", __VA_ARGS__)
			#define LOG_ERROR(...)			__android_log_print(ANDROID_LOG_ERROR, "ByteCat", __VA_ARGS__)
			#define LOG_CRITICAL(x)			__android_log_print(ANDROID_LOG_FATAL, "ByteCat", x)
			#define LOG_ASSERT(x, ...)		
		#endif
	#endif

	// Client log/assert macros
	#ifdef BC_CLIENT_ACCESS
		#ifdef BC_PLATFORM_PC
			#define LOG_INFO(...)			::BC::Log::GetClientLogger()->info(__VA_ARGS__)
			#define LOG_WARN(...)			::BC::Log::GetClientLogger()->warn(__VA_ARGS__)
			#define LOG_ERROR(...)			::BC::Log::GetClientLogger()->error(__VA_ARGS__)
			#define LOG_CRITICAL(x)			::BC::Log::GetClientLogger()->critical(x)
			#define LOG_ASSERT(x, ...)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BC_DEBUG_BREAK; } }
		#elif defined(BC_PLATFORM_ANDROID)
			#define LOG_ESSENTIAL(x)		__android_log_print(ANDROID_LOG_VERBOSE, "ByteCatApp", x);
			#define LOG_INFO(...)			__android_log_print(ANDROID_LOG_INFO, "ByteCatApp", __VA_ARGS__)
			#define LOG_WARN(...)			__android_log_print(ANDROID_LOG_WARN, "ByteCatApp", __VA_ARGS__)
			#define LOG_ERROR(...)			__android_log_print(ANDROID_LOG_ERROR, "ByteCatApp", __VA_ARGS__)
			#define LOG_CRITICAL(x)			__android_log_print(ANDROID_LOG_FATAL, "ByteCatApp", x)
			#define LOG_ASSERT(x, ...)		
		#endif
	#endif
#else
	// Only necessary logs
	#ifdef BC_PLATFORM_PC
		#define LOG_ESSENTIAL(x)			std::cout << (x) << std::endl
		#define LOG_CRITICAL(x)				std::cerr << (x) << std::endl
	#elif defined(BC_PLATFORM_ANDROID)
		#define LOG_ESSENTIAL(x)			__android_log_print(ANDROID_LOG_VERBOSE, "ByteCat", x)
		#define LOG_CRITICAL(x)				__android_log_print(ANDROID_LOG_FATAL, "ByteCat", x)
	#endif

	#define LOG_TEXT_LONG(x)
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
	#define LOG_ASSERT(x, ...)
#endif

namespace BC
{
	class Log
	{
	private:		
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
		
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	#ifdef BC_CORE_ACCESS
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
	#endif
	};
}