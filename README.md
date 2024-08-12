# 42_V_scop

## Ubuntu 22.04LTS!

## Install dependencies
- GLFW ```sudo apt install libwayland-dev libxkbcommon-dev xorg-dev```
- GLEW:```sudo apt install build-essential libxmu-dev libxi-dev libgl-dev libglu1-mesa-dev```

## Run the project
- ```make```

## GLFW
- GLFW is a lightweight utility library primarily developed for use with OpenGL. It provides the programmer with the convenience of creating 'context' and windows for OpenGL and Vulkan, and managing keyboard, mouse and joystick input and output, regardless of the operating system they are working on.
- [Starter code](https://www.glfw.org/documentation.html)
- [Download source code](https://www.glfw.org/download.html)
- [Build and Compile source code](https://www.glfw.org/docs/latest/compile.html)
- if glClear not found, then also link it: -lGL

## GLEW
- The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library. GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.
- GLEW needs an openGL window open first.
- do```#include <GL/glew.h>``` before ```#include <GLFW/glfw3.h>```
