cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/glfw)

find_package(OpenGL REQUIRED)

add_executable(video-app src/main.cpp)
target_link_libraries(video-app glfw OpenGL::GL)