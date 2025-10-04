#!/bin/bash

if [ "$1" == "clean" ] || [ "$1" == "c" ]; then
  echo "Cleaning"
  cd build
  make clean
  cd ..
  exit 0
fi

cd build
make
cd ..
echo "Library Compiled"
make
echo "Executable Compiled"

if [ "$1" == "run" ] || [ "$1" == "r" ]; then
  echo "Running Game"
  echo ""
  ./game
fi