file(GLOB_RECURSE APP_SRC_FILES CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${APP_SRC_FILES})

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

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory 
    "${CMAKE_CURRENT_SOURCE_DIR}/${ASSETS_FOLDER}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${ASSETS_FOLDER}")