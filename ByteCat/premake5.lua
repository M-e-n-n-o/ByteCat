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
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"BC_CORE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{Libs.GLEW}/include",
		"%{Libs.GLFW}/include",
		"%{Libs.ImGui}",
		"%{Libs.GLM}"
	}

	links
	{
		"glew32",
		"GLFW",
		"ImGui",
		"GLM",
		"opengl32.lib"
	}

	libdirs
	{
		"%{Libs.GLEW}/x64/lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

		prebuildcommands
		{
			("{COPY} vendor/glew-2.0.0/x64/glew32.dll ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "system:linux"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_LINUX"
		}

		prebuildcommands
		{
			("{COPY} vendor/glew-2.0.0/x64/glew32.dll ../bin/" .. outputdir .. "/Sandbox")
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
