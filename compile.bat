@ECHO off

IF "%1 "== "clean" (
    echo Cleaning
    cd build
    make clean
    cd ..
    exit
)

IF "%1" == "c" (
    echo Cleaning
    cd build
    make clean
    cd ..
    exit
)

cd build
make
cd ..
echo Library Compiled
make
echo Executable Compiled
IF "%1 "== "run" (
    echo Running Game
    echo ""
    .\game.exe
)

IF "%1" == "r" (
    echo Running Game
    echo.
    .\game.exe
)