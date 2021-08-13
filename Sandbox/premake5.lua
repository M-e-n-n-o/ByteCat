project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"	

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../ByteCat/vendor/spdlog/include",
		"../ByteCat/src",
		"../ByteCat/vendor",
		"%{Libs.GLM}"
	}

	linkgroups "on"

	links
	{
		"ByteCat"
	}

	filter "system:windows"
		systemversion "latest"

		postbuildcommands
		{
			("{COPY} res/* ../bin/" .. outputdir .. "/Sandbox/res")
		}

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		pic "on"
		systemversion "latest"

		links
		{
			"dl",
			"GL",
			"GLU",
			"X11",
			"Xxf86vm",
			"Xrandr",
			"pthread",
			"Xi",
			"GLFW",
			"GLAD",
			"ImGui"
		}

		postbuildcommands
		{
			("cp -R ./res ../bin/" .. outputdir .. "/Sandbox")
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
