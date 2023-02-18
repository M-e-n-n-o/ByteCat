file(GLOB_RECURSE APP_SRC_FILES CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
)

if (BUILD_PC)
    add_executable(${PROJECT_NAME} ${APP_SRC_FILES})
elseif (BUILD_MOBILE)
    add_library(${PROJECT_NAME} SHARED ${APP_SRC_FILES})

    set(GLFM_APP_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
endif()


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

# Add post build command to copy assets directory to build location
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/${ASSETS_FOLDER}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${ASSETS_FOLDER}")