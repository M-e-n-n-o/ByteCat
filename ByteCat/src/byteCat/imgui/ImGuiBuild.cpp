#include "bcpch.h"

#if defined(BC_PLATFORM_WINDOWS) || defined(BC_PLATFORM_LINUX)
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#include "imgui_impl_opengl3.cpp"
	#include "imgui_impl_glfw.cpp"
#endif