PROJECT_NAME = game

default: build
	g++ main.cpp bin/Debug-x64/libDuckyLib.a -o $(PROJECT_NAME) -lSDL3 -lpthread -lm -ldl

build:
	cd build
	make all
	cd ..
