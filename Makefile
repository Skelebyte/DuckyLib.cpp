PROJECT_NAME = game

default: premake_setup build
	g++ main.cpp bin/Debug-x64/libDuckyLib.a -o $(PROJECT_NAME) -lSDL3 -lpthread -lm -ldl

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