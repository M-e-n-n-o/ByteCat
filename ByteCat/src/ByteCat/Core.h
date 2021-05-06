#pragma once

#ifdef BC_PLATFORM_WINDOWS

	#define BC_DEBUG_BREAK __debugbreak()

	#ifdef BC_BUILD_DLL
		#define BYTECAT_API __declspec(dllexport)
		#define BC_CORE_ACCESS
	#else
		#define BYTECAT_API __declspec(dllimport)
		#define BC_CLIENT_ACCESS
	#endif

#else
	#define BC_PLATFORM_NONE
	#error ByteCat does not support your platform right now :(
#endif

#ifdef BC_DEBUG
	#define BC_ENABLE_LOG
#endif

#define BIT(x) (1 << x)

namespace BC
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
