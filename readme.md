[![wakatime](https://wakatime.com/badge/user/ebdd5199-39f1-41e1-aa46-73f4e53797cb/project/e708815b-f08a-47a1-8da3-91a45c945786.svg)](https://wakatime.com/badge/user/ebdd5199-39f1-41e1-aa46-73f4e53797cb/project/e708815b-f08a-47a1-8da3-91a45c945786)

# DuckyLib.cpp

Simple C++ game engine powered by SDL 3 and OpenGL.

## Windows instructions

### 1. Install [Premake5](https://premake.github.io/download)

### 2. Install msys2, install the required packages in the MSYS2 MINGW terminal

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

### 3. Run the following commands in Windows terminal

```bash
premake5 gmake
cd build
make
cd ..
make
```
