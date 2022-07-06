cmake_minimum_required(VERSION 3.16.3)

project(ByteCatApplication VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ByteCat/vendor/GLFW)
add_subdirectory(ByteCat/vendor/Glad)
add_subdirectory(ByteCat/vendor/imgui)

add_compile_definitions(
    _CRT_SECURE_NO_WARNINGS
    GLFW_INCLUDE_NONE
    BC_PLATFORM_WINDOWS
    BC_CORE
    BC_DEBUG
)

add_subdirectory(Sandbox)
add_subdirectory(ByteCat)

# include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)