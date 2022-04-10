#include "bcpch.h"

#ifdef BC_PLATFORM_WINDOWS || BC_PLATFORM_LINUX
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#include "examples/imgui_impl_opengl3.cpp"
	#include "examples/imgui_impl_glfw.cpp"
#endif