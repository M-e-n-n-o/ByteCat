#pragma once

#include "byteCat/Platform.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


// Logging
#ifdef BC_ENABLE_LOG

	#define LOG_TEXT_LONG(x)			std::cout << (x) << std::endl

	// Core log/assert macros
	#ifdef BC_CORE_ACCESS
		#define LOG_ESSENTIAL(x)		::BC::Log::GetCoreLogger()->info(x)
		#define LOG_INFO(...)			::BC::Log::GetCoreLogger()->info(__VA_ARGS__)
		#define LOG_WARN(...)			::BC::Log::GetCoreLogger()->warn(__VA_ARGS__)
		#define LOG_ERROR(...)			::BC::Log::GetCoreLogger()->error(__VA_ARGS__)
		#define LOG_CRITICAL(x)			::BC::Log::GetCoreLogger()->critical(x)
		#define LOG_ASSERT(x, ...)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BC_DEBUG_BREAK; } }
	#endif

	// Client log/assert macros
	#ifdef BC_CLIENT_ACCESS
	#define LOG_INFO(...)				::BC::Log::GetClientLogger()->info(__VA_ARGS__)
		#define LOG_WARN(...)			::BC::Log::GetClientLogger()->warn(__VA_ARGS__)
		#define LOG_ERROR(...)			::BC::Log::GetClientLogger()->error(__VA_ARGS__)
		#define LOG_CRITICAL(x)		::BC::Log::GetClientLogger()->critical(x)
		#define LOG_ASSERT(x, ...)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); BC_DEBUG_BREAK; } }
	#endif
#else
	#include <iostream>

	// Only necessary logs
	#define LOG_TEXT_LONG(x)
	#define LOG_ESSENTIAL(x)			std::cout << (x) << std::endl
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
	#define LOG_CRITICAL(x)				std::cerr << (x) << std::endl
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