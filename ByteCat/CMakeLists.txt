file(GLOB_RECURSE BYTECAT_SRC_FILES CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
    "vendor/stb_image/*.h"
    "vendor/stb_image/*.cpp"
    "vendor/glm/glm/*.hpp"
    "vendor/glm/glm/*.inl"
)

add_library(ByteCat STATIC ${BYTECAT_SRC_FILES})

target_compile_definitions(ByteCat PRIVATE BC_CORE)

target_precompile_headers(ByteCat PRIVATE "src/bcpch.h")

target_include_directories(ByteCat PUBLIC
    "src"
    "vendor/spdlog/include"
    "vendor/glad/include"
    "vendor/glfw/include"
    "vendor/imgui/imgui"
    "vendor/glm"
    "vendor/stb_image"
)

target_link_directories(ByteCat PUBLIC
    "ByteCat/vendor/glfw/src"
    "ByteCat/vendor/glad"
    "ByteCat/vendor/imgui/imgui"
)

target_link_libraries(ByteCat PUBLIC
    glfw
    glad
    ImGui
)
