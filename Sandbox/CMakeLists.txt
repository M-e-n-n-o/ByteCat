file(GLOB_RECURSE SANDBOX_SRC_FILES CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SANDBOX_SRC_FILES})

#  add_compile_definitions(BC_CLIENT)
target_include_directories(${PROJECT_NAME} PUBLIC
    "../ByteCat/vendor/spdlog/include"
    "../ByteCat/src"
    "../ByteCat/vendor"
    "../ByteCat/vendor/glm"
)

# Link ByteCat
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/ByteCat/src")
target_link_directories(${PROJECT_NAME} PUBLIC ByteCat)
target_link_libraries(${PROJECT_NAME} ByteCat)