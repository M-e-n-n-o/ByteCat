workspace "ByteCat"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

Libs = {}
Libs["GLFW"] = "ByteCat/vendor/GLFW"
Libs["GLEW"] = "ByteCat/vendor/glew-2.0.0"
Libs["GLM"] = "ByteCat/vendor/glm"
Libs["ImGui"] = "ByteCat/vendor/imgui"

include "ByteCat/vendor/GLFW"
include "ByteCat/vendor/glm"
include "ByteCat/vendor/imgui"


project "ByteCat"
	location "ByteCat"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bcpch.h"
	pchsource "ByteCat/src/bcpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"BC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		prebuildcommands
		{
			("{COPY} vendor/glew-2.0.0/x64/glew32.dll ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_LINUX",
			"BC_BUILD_DLL"
		}

		prebuildcommands
		{
			("{COPY} vendor/glew-2.0.0/x64/glew32.dll ../bin/" .. outputdir .. "/Sandbox")
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ByteCat/vendor/spdlog/include",
		"ByteCat/src",
		"%{Libs.GLM}"
	}

	links
	{
		"ByteCat",
		"GLM"
	}

	postbuildcommands
	{
		("{COPY} res/* ../bin/" .. outputdir .. "/Sandbox/res")
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BC_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		buildoptions "/MD"
		optimize "On"