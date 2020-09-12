# How to compile the video-app
1. Make a build folder directory using "mkdir build"
2. Navigate to build folder through bash
3. Type "cmake .." to compile and build project into the build folder e.g

## Find executable .exe
* Navigate to debug folder in build
* Double click on exe to open

## Open in VS studio
* Make sure to cmkae build project before into build directory.
* in build directory open a new ffmpeg directory under lib eg. build/lib/FFmpeg
* Copy lib files form lib/ffmpeg/dev/lib into build/lib/FFmpeg
* Double click on video-app.vcxproj to open visual studio.

## Dependency /Libs
* glfw (OpenGL)
* ffmpeg zeranoe builds [shared&dev]


./configure --disable-x86asm --enable-shared --disable-static  --libdir=/libs

