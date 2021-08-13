project "ByteCat"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bcpch.h"
	pchsource "src/bcpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"BC_CORE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{Libs.GLAD}/include",
		"%{Libs.GLFW}/include",
		"%{Libs.ImGui}",
		"%{Libs.GLM}",
		"%{Libs.StbImage}"
	}

	linkgroups "on"

	links
	{
		"GLFW",
		"Glad",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		links
		{
			"opengl32.lib"
		}

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		systemversion "latest"

		links
		{
			"GL",
			"X11",
			"phthread"
		}

		defines
		{
			"BC_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BC_DIST"
		runtime "Release"
		optimize "on"
