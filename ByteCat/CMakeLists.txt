file(GLOB_RECURSE BYTECAT_SRC_FILES CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
    "vendor/stb_image/*.h"
    "vendor/stb_image/*.cpp"
    "vendor/glm/glm/*.hpp"
    "vendor/glm/glm/*.inl"
)

add_library(ByteCat STATIC ${BYTECAT_SRC_FILES})

target_precompile_headers(ByteCat PRIVATE "src/bcpch.h")

target_include_directories(ByteCat PUBLIC
    "src"
    "vendor/spdlog/include"
    "vendor/Glad/include"
    "vendor/GLFW/include"
    "vendor/imgui"
    "vendor/glm"
    "vendor/stb_image"
)

# find_package(OpenGL)
target_link_directories(ByteCat PUBLIC
    "ByteCat/vendor/GLFW/src"
    "ByteCat/vendor/Glad"
    "ByteCat/vendor/ImGui"
)

target_link_libraries(ByteCat
    glfw
    Glad
    ImGui
)
