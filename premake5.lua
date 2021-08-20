include "dependencies.lua"

workspace "ByteCat"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Dependencies
include "ByteCat/vendor/GLFW"
include "ByteCat/vendor/imgui"
include "ByteCat/vendor/Glad"
include "ByteCat/vendor/lua"

-- ByteCat projects
include "ByteCat"
include "Sandbox"
