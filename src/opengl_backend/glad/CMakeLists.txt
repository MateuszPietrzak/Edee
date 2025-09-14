project(glad)
add_library(glad include/glad/glad.h src/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(glad PUBLIC include/)
