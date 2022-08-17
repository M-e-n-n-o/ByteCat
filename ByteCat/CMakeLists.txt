file(GLOB_RECURSE BYTECAT_SRC_FILES CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
    "vendor/stb_image/*.h"
    "vendor/stb_image/*.cpp"
    "vendor/glm/glm/*.hpp"
    "vendor/glm/glm/*.inl"
)

add_library(ByteCat STATIC ${BYTECAT_SRC_FILES})

# Give ByteCat core access to itself
target_compile_definitions(ByteCat PRIVATE BC_CORE)

# Set precompiled header
target_precompile_headers(ByteCat PRIVATE "src/bcpch.h")

target_include_directories(ByteCat PUBLIC
    "src"
    "vendor/spdlog/include"
    "vendor/imgui/imgui"
    "vendor/glm"
    "vendor/stb_image"
)

target_link_directories(ByteCat PUBLIC
    "ByteCat/vendor/imgui/imgui"
)

# Link external libraries
target_link_libraries(ByteCat PUBLIC
    ImGui
)

if (BUILD_PC)
    target_include_directories(ByteCat PUBLIC
        "vendor/glad/include"
        "vendor/glfw/include"
    )

    target_link_directories(ByteCat PUBLIC
        "ByteCat/vendor/glfw/src"
        "ByteCat/vendor/glad"
    )

    target_link_libraries(ByteCat PUBLIC
        glfw
        glad
    )
elseif(BUILD_MOBILE)
    find_library(log-lib log)
    find_library(android-lib android)
    find_library(EGL-lib EGL)
    find_library(GLESv2-lib GLESv2)

    target_include_directories(ByteCat PUBLIC
        "vendor/glfm/include"
    )

    target_link_directories(ByteCat PUBLIC
        "ByteCat/vendor/glfm/src"
    )

    # Link external libraries
    target_link_libraries(ByteCat PUBLIC
        glfm
    )
endif()
