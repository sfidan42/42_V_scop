#!/bin/bash -e

cd glfw-3.4
cmake -S . -B build
make -C build
mkdir -p ../lib ../inc
mv build/src/libglfw3.a ../lib
cp -r include/GLFW ../inc
