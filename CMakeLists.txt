cmake_minimum_required(VERSION 3.12)
project(edee CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(sol2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(LUA REQUIRED lua5.4)

add_subdirectory(src/opengl_backend)

add_executable(edee
  src/main.cpp
  src/edee.cpp
  src/plugin.cpp)


target_link_libraries(edee PUBLIC glad opengl_backend)
target_link_libraries(edee PRIVATE sol2::sol2 ${LUA_LIBRARIES})

target_include_directories(edee PRIVATE ${LUA_INCLUDE_DIRS})
