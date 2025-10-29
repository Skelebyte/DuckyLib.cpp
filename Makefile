PROJECT_NAME = game
WINDOWS_EXT = .exe
LINUX_EXT = 

EXECUTABLE = 

WINDOWS_SDL_INCL = duckylib/third_party/SDL3/include

WINDOWS_LIB = bin\Debug-x64\DuckyLib.lib
LINUX_LIB = bin/Debug-x64/libDuckyLib.a

FLAGS = 

WINDOWS_FLAGS = -lSDL3 -L$(WINDOWS_LIB) -lpthread -lm -lopengl32 -static-libgcc -static libstdc++
LINUX_FLAGS = -lSDL3 -lpthread -lm -ldl

ifeq ($(OS),Windows_NT)
	EXECUTABLE +=$(PROJECT_NAME)$(WINDOWS_EXT)
	FLAGS += $(WINDOWS_LIB) -o $(EXECUTABLE) $(WINDOWS_FLAGS)
else
	EXECUTABLE += $(PROJECT_NAME)$(LINUX_EXT)
	FLAGS +=  $(LINUX_LIB) -o $(EXECUTABLE) $(LINUX_FLAGS)
endif

default: premake_setup build
	g++ main.cpp $(FLAGS)

premake_setup:
	premake5 gmake

build:
	cd build
	make all
	cd ..


cleanup:
	cd build
	make clean
	cd ..