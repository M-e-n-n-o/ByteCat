add_library(Glad STATIC
    "include/glad/glad.h"
    "include/KHR/khrplatform.h"
    "src/glad.c"
)

target_include_directories(Glad PUBLIC "include")