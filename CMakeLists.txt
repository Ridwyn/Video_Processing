cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/glfw)

find_package(OpenGL REQUIRED)


# Copy ffmpeg .lib libraries to lib destination for vs studio
file(COPY lib/ffmpeg/dev/lib/avcodec.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/dev/lib/avfilter.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/dev/lib/avdevice.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/dev/lib/avformat.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/dev/lib/swresample.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/dev/lib/avutil.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/dev/lib/swscale.lib DESTINATION lib/FFmpeg PATTERN build EXCLUDE)

# Path to FFmpeg lib after cmake build
list(APPEND LIBSLINK
    lib/FFmpeg/avcodec
    lib/FFmpeg/avfilter
    lib/FFmpeg/avdevice
    lib/FFmpeg/avformat
    lib/FFmpeg/swresample
    lib/FFmpeg/avutil
    lib/FFmpeg/swscale
)

#Copy ffmpeg .dll to Debug directory needed for executables to run
file(COPY lib/ffmpeg/shared/avcodec-58.dll DESTINATION Debug PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/shared/avfilter-7.dll DESTINATION Debug PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/shared/avdevice-58.dll DESTINATION Debug PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/shared/avformat-58.dll DESTINATION Debug PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/shared/swresample-3.dll DESTINATION Debug PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/shared/avutil-56.dll DESTINATION Debug PATTERN build EXCLUDE)
file(COPY lib/ffmpeg/shared/swscale-5.dll DESTINATION Debug PATTERN build EXCLUDE)


list(APPEND INCLUDES
    lib/ffmpeg/dev/include/libavcodec
    lib/ffmpeg/dev/include/libavfilter
    lib/ffmpeg/dev/include/libavdevice
    lib/ffmpeg/dev/include/libavformat
    lib/ffmpeg/dev/include/libavutil
    lib/ffmpeg/dev/include/libswresample
    lib/ffmpeg/dev/include/libswscale
)
list(APPEND LIBS
    lib/ffmpeg/dev/lib/avcodec.lib
    lib/ffmpeg/dev/lib/avfilter.lib
    lib/ffmpeg/dev/lib/avdevice.lib
    lib/ffmpeg/dev/lib/avformat.lib
    lib/ffmpeg/dev/lib/avutil.lib
    lib/ffmpeg/dev/lib/swresample.lib
    lib/ffmpeg/dev/lib/swscale.lib
)

list(APPEND SOURCES
    src/main.cpp
    src/load_frame.cpp
)



add_executable(video-app ${SOURCES}  ${INCLUDES} )
target_include_directories(video-app PUBLIC ${INCLUDES})
target_link_libraries(video-app glfw OpenGL::GL ${LIBSLINK})

