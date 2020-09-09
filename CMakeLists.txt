cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/glfw)

find_package(OpenGL REQUIRED)


find_library (ffmpeg  PATHS  lib/ffmpeg)
find_library (libavcodec "avcodec" PATHS  /lib/ffmpeg/libavcodec/avcodec.h NO_DEFAULT_PATH)
find_library (libavfilter  PATHS  lib/ffmpeg/libavfilter)
find_library (libavdevice  PATHS  lib/ffmpeg/libavdevice)
find_library (libavformat  PATHS  lib/ffmpeg/libavformat)
find_library (libavresample  PATHS  lib/ffmpeg/libavresample)
find_library (libavutil  PATHS  lib/ffmpeg/libavutil)
find_library (libswscale  PATHS  lib/ffmpeg/libswscale)


add_executable(video-app src/main.cpp)
target_include_directories(video-app PUBLIC lib/ffmpeg/libavcodec lib/ffmpeg/libavfilter lib/ffmpeg/libavdevice lib/ffmpeg/libavformat lib/ffmpeg/libavresample lib/ffmpeg/libavutil lib/ffmpeg/libswscale lib/ffmpeg)
target_link_libraries(video-app glfw OpenGL::GL)

