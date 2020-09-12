# How to compile the video-app
1. Make a build folder directory using "mkdir build"
2. Navigate to build folder through bash
3. Type "cmake .." to compile and build project into the build folder e.g

## Build executable
* In build directory run "cmake --build . --target video-app" to build a video-app.exe or add --config Debug to build in debug mode
* Open executable in Debug directory



## Dependency /Libs
* glfw (OpenGL)
* ffmpeg zeranoe builds [shared+dev]


./configure --disable-x86asm --enable-shared --disable-static  --libdir=/libs

