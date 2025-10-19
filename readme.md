# DuckyLib.cpp

Simple C++ game engine powered by SDL 3 and OpenGL.

## Windows instructions

### 1. Install [Premake5](https://premake.github.io/download)

### 2. Install msys2, install the required packages

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
pacman -S mingw-w64-ucrt-x86_64-sdl3
```

### 3. Run the following commands in Windows terminal

```bash
premake5 gmake
cd build
make
cd ..
make
```
