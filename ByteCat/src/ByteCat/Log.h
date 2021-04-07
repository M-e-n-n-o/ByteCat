#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// Core log macros
#define BC_CORE_TRACE(...)    ::ByteCat::Log::getCoreLogger()->trace(__VA_ARGS__)
#define BC_CORE_INFO(...)     ::ByteCat::Log::getCoreLogger()->info(__VA_ARGS__)
#define BC_CORE_WARN(...)     ::ByteCat::Log::getCoreLogger()->warn(__VA_ARGS__)
#define BC_CORE_ERROR(...)    ::ByteCat::Log::getCoreLogger()->error(__VA_ARGS__)
#define BC_CORE_CRITICAL(...) ::ByteCat::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define BC_TRACE(...)         ::ByteCat::Log::getClientLogger()->trace(__VA_ARGS__)
#define BC_INFO(...)          ::ByteCat::Log::getClientLogger()->info(__VA_ARGS__)
#define BC_WARN(...)          ::ByteCat::Log::getClientLogger()->warn(__VA_ARGS__)
#define BC_ERROR(...)         ::ByteCat::Log::getClientLogger()->error(__VA_ARGS__)
#define BC_CRITICAL(...)      ::ByteCat::Log::getClientLogger()->critical(__VA_ARGS__)

namespace ByteCat
{
	class BYTECAT_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;

	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
	};
}