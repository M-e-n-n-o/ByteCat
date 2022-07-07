cmake_minimum_required(VERSION 3.16.3)

project(ByteCatApplication VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

add_definitions(
    -DGLFW_BUILD_DOCS=OFF
    -DGLFW_INSTALL=OFF
)

add_subdirectory(ByteCat/vendor/glfw)
add_subdirectory(ByteCat/vendor/glad)
add_subdirectory(ByteCat/vendor/imgui)

set(ASSETS_FOLDER assets/)

add_compile_definitions(
    _CRT_SECURE_NO_WARNINGS
    GLFW_INCLUDE_NONE
    BC_VERSION="${CMAKE_PROJECT_VERSION}"
    BC_ASSETS_FOLDER="${ASSETS_FOLDER}"
    $<$<CONFIG:Debug>:BC_DEBUG>
    $<$<CONFIG:Release>:BC_RELEASE>
    $<$<CONFIG:RelWithDebInfo>:BC_RELEASE>
    $<$<CONFIG:MinSizeRel>:BC_DIST>
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