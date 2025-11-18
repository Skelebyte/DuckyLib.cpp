PROJECT_NAME = game
WINDOWS_EXT = .exe
LINUX_EXT = 

EXECUTABLE = 

WINDOWS_SDL_INCL = duckylib\third_party\SDL3\include

WINDOWS_LIB = bin\Debug-x64\DuckyLib.lib duckylib\third_party\libs\windows\SDL3.lib #duckylib\third_party\libs\windows\Imgui.lib duckylib\third_party\libs\windows\assimp-vc143-mtd.lib
LINUX_LIB = bin/Debug-x64/libDuckyLib.a duckylib/third_party/libs/linux/libassimp.a duckylib/third_party/libs/linux/libSDL3.a duckylib/third_party/libs/linux/libImgui.a

FLAGS = 

WINDOWS_FLAGS = -I$(WINDOWS_SDL_INCL) -lSDL3 -L$(WINDOWS_LIB) -lpthread -lm -lopengl32 -static-libgcc -static-libstdc++ -Wattributes
LINUX_FLAGS = -lSDL3 -lpthread -lm -ldl #-lassimp

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

editor: premake_setup build
	g++ duckylib/editor/editor_main.cpp $(FLAGS)

cleanup:
	cd build
	make clean
	cd ..