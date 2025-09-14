set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_subdirectory(glad)

add_library(opengl_backend
  opengl_backend.cpp
)

target_link_libraries(opengl_backend PUBLIC glad glfw OpenGL::GL)
