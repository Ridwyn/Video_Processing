cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/glfw)

find_package(OpenGL REQUIRED)


list(APPEND LIBSLINK
    lib/FFmpeg/avcodec
    lib/FFmpeg/avfilter
    lib/FFmpeg/avdevice
    lib/FFmpeg/avformat
    lib/FFmpeg/swresample
    lib/FFmpeg/avutil
    lib/FFmpeg/swscale
)

list(APPEND INCLUDES
    lib/ffmpeg/dev/include/libavcodec
    lib/ffmpeg/dev/include/libavfilter
    lib/ffmpeg/dev/include/libavdevice
    lib/ffmpeg/dev/include/libavformat
    lib/ffmpeg/dev/include/libavutil
    lib/ffmpeg/dev/include/libswresample
    lib/ffmpeg/dev/include/libswscale
)

list(APPEND SOURCES
    src/main.cpp
    src/load_frame.cpp
)



add_executable(video-app ${SOURCES}  ${INCLUDES} )
target_include_directories(video-app PUBLIC ${INCLUDES})
target_link_libraries(video-app glfw OpenGL::GL ${LIBSLINK} )

