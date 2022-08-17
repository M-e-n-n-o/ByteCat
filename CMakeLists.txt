cmake_minimum_required(VERSION 3.16.3)

project(ByteCatApplication VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_SYSTEM_NAME MATCHES "Windows" OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(BUILD_PC ON)

    if(CMAKE_SYSTEM_NAME MATCHES "Windows")
        add_compile_definitions(BC_PLATFORM_WINDOWS)
    else()
        add_compile_definitions(BC_PLATFORM_LINUX)
    endif()

    # Set external library options
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)

    # Add external PC libraries
    add_subdirectory(ByteCat/vendor/glfw)
    add_subdirectory(ByteCat/vendor/glad)
elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
    set(BUILD_MOBILE ON)
    add_compile_definitions(BC_PLATFORM_ANDROID)

    # Add external mobile libraries
    add_subdirectory(ByteCat/vendor/glfm)
endif()

# Add external generic libraries
add_subdirectory(ByteCat/vendor/imgui)

# Set assets folder
set(ASSETS_FOLDER assets/)

# Add preprocessor definitions
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

# Add main projects
# add_subdirectory(App)
add_subdirectory(ByteCat)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)