#pragma once

#include "byteCat/Platform.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/bundled/printf.h"

#ifdef BC_PLATFORM_PC
	#include <iostream>

	#define SPDLOG_LOGGER_PRINTF(logger, level, ...) \
		Log::Loglineprintf(logger, level, spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, __VA_ARGS__)

#elif defined(BC_PLATFORM_ANDROID)
	#include <android/log.h>
#endif

// Logging
#ifdef BC_ENABLE_LOG

	#ifdef BC_PLATFORM_PC
		#define LOG_TEXT_LONG(x)			std::cout << (x) << std::endl
	#elif defined(BC_PLATFORM_ANDROID)
		#define LOG_TEXT_LONG(x)			__android_log_print(ANDROID_LOG_VERBOSE, "", "%s", x)
	#endif

	// Core log/assert macros
	#ifdef BC_CORE_ACCESS
		#ifdef BC_PLATFORM_PC
			#define LOG_ESSENTIAL(x)		::BC::Log::GetCoreLogger()->info(x)
			#define LOG_INFO(...)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetCoreLogger(), spdlog::level::info, __VA_ARGS__)
			#define LOG_WARN(...)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetCoreLogger(), spdlog::level::warn, __VA_ARGS__)
			#define LOG_ERROR(...)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetCoreLogger(), spdlog::level::err, __VA_ARGS__)
			#define LOG_CRITICAL(x)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetCoreLogger(), spdlog::level::critical, x)
			#define LOG_ASSERT(x, y)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", y); BC_DEBUG_BREAK; } }
		#elif defined(BC_PLATFORM_ANDROID)
			#define LOG_ESSENTIAL(x)		__android_log_print(ANDROID_LOG_VERBOSE, "ByteCat", x)
			#define LOG_INFO(...)			__android_log_print(ANDROID_LOG_INFO, "ByteCat", __VA_ARGS__)
			#define LOG_WARN(...)			__android_log_print(ANDROID_LOG_WARN, "ByteCat", __VA_ARGS__)
			#define LOG_ERROR(...)			__android_log_print(ANDROID_LOG_ERROR, "ByteCat", __VA_ARGS__)
			#define LOG_CRITICAL(x)			__android_log_print(ANDROID_LOG_FATAL, "ByteCat", x)
			#define LOG_ASSERT(x, y)		
		#endif
	#endif

	// Client log/assert macros
	#ifdef BC_CLIENT_ACCESS
		#ifdef BC_PLATFORM_PC
			#define LOG_INFO(...)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetClientLogger(), spdlog::level::info, __VA_ARGS__)
			#define LOG_WARN(...)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetClientLogger(), spdlog::level::warn, __VA_ARGS__)
			#define LOG_ERROR(...)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetClientLogger(), spdlog::level::err, __VA_ARGS__)
			#define LOG_CRITICAL(x)			SPDLOG_LOGGER_PRINTF(::BC::Log::GetClientLogger(), spdlog::level::critical, x)
			#define LOG_ASSERT(x, y)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", y); BC_DEBUG_BREAK; } }
		#elif defined(BC_PLATFORM_ANDROID)
			#define LOG_ESSENTIAL(x)		__android_log_print(ANDROID_LOG_VERBOSE, "ByteCatApp", x);
			#define LOG_INFO(...)			__android_log_print(ANDROID_LOG_INFO, "ByteCatApp", __VA_ARGS__)
			#define LOG_WARN(...)			__android_log_print(ANDROID_LOG_WARN, "ByteCatApp", __VA_ARGS__)
			#define LOG_ERROR(...)			__android_log_print(ANDROID_LOG_ERROR, "ByteCatApp", __VA_ARGS__)
			#define LOG_CRITICAL(x)			__android_log_print(ANDROID_LOG_FATAL, "ByteCatApp", x)
			#define LOG_ASSERT(x, y)		
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

		template <class loggerPtr, class... Args>
		static void Loglineprintf(loggerPtr logger,
			spdlog::level::level_enum level,
			spdlog::source_loc loc,
			const char* fmt,
			const Args&... args) noexcept
		{
			if (logger && logger->should_log(level))
			{
				logger->log(loc, level, "{}", fmt::sprintf(fmt, args...));
			}
		}
		
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	#ifdef BC_CORE_ACCESS
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
	#endif
	};
}
