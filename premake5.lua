include "dependencyList.lua"

workspace "ByteCat"
	architecture "x64"
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
include "ByteCat/vendor/glm"
include "ByteCat/vendor/imgui"

-- ByteCat projects
include "ByteCat"
include "Sandbox"