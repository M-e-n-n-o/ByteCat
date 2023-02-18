#include "bcpch.h"

#ifdef BC_PLATFORM_PC
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#include "imgui_impl_opengl3.cpp"
	#include "imgui_impl_glfw.cpp"
#elif defined(BC_PLATFORM_ANDROID)
	// ImGui is disabled on Android for now
#endif