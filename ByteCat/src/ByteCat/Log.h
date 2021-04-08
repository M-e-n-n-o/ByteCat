#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


// Logging
#ifdef BC_ENABLE_LOG
	// Core log macros
	#define BC_CORE_TRACE(...)    ::ByteCat::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define BC_CORE_INFO(...)     ::ByteCat::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define BC_CORE_WARN(...)     ::ByteCat::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define BC_CORE_ERROR(...)    ::ByteCat::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define BC_CORE_CRITICAL(...) ::ByteCat::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client log macros
	#define BC_TRACE(...)         ::ByteCat::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define BC_INFO(...)          ::ByteCat::Log::GetClientLogger()->info(__VA_ARGS__)
	#define BC_WARN(...)          ::ByteCat::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define BC_ERROR(...)         ::ByteCat::Log::GetClientLogger()->error(__VA_ARGS__)
	#define BC_CRITICAL(...)      ::ByteCat::Log::GetClientLogger()->critical(__VA_ARGS__)

	// Asserting
	#define BC_ASSERT(x, ...) { if(!(x)) { BC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BC_CORE_ASSERT(x, ...) { if(!(x)) { BC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	// Empty core log macros
	#define BC_CORE_TRACE(...)
	#define BC_CORE_INFO(...)
	#define BC_CORE_WARN(...)
	#define BC_CORE_ERROR(...)
	#define BC_CORE_CRITICAL(...)

	// Empty client log macros
	#define BC_TRACE(...)
	#define BC_INFO(...)
	#define BC_WARN(...)
	#define BC_ERROR(...)
	#define BC_CRITICAL(...)

	// Asserting
	#define BC_ASSERT(x, ...)
	#define BC_CORE_ASSERT(x, ...)
#endif

namespace ByteCat
{
	class BYTECAT_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; }
	};
}