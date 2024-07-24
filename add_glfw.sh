#!/bin/bash -e
wget https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
unzip glfw-3.4.zip
cd glfw-3.4
cmake -S . -B build
make -C build
mkdir -p ../lib ../inc
mv build/src/libglfw3.a ../lib
cp -r include/GLFW ../inc
