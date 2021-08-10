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
		"BC_CORE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{Libs.GLEW}/include",
		"%{Libs.GLFW}/include",
		"%{Libs.ImGui}",
		"%{Libs.GLM}",
		"%{Libs.StbImage}"
	}

	links
	{
		"glew32",
		"GLFW",
		"ImGui",
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
