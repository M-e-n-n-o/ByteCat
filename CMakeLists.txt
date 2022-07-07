cmake_minimum_required(VERSION 3.16.3)

list(APPEND CMAKE_CONFIGURATION_TYPES
    Debug
    Release
    Dist
)

project(ByteCatApplication VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ByteCat/vendor/glfw)
add_subdirectory(ByteCat/vendor/glad)
add_subdirectory(ByteCat/vendor/imgui)

add_definitions(
    -DGLFW_BUILD_DOCS=OFF
    -DGLFW_INSTALL=OFF
)

add_compile_definitions(
    _CRT_SECURE_NO_WARNINGS
    GLFW_INCLUDE_NONE
    $<$<CONFIG:Debug>:BC_DEBUG>
    $<$<CONFIG:Release>:BC_RELEASE>
    $<$<CONFIG:Dist>:BC_DIST>
)

if(WIN32)
    add_compile_definitions(BC_PLATFORM_WINDOWS)
elseif(UNIX)
    add_compile_definitions(BC_PLATFORM_LINUX)
endif()

add_subdirectory(Sandbox)
add_subdirectory(ByteCat)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)