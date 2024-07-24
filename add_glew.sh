#!/bin/bash -e

[ -d glew-2.1.0.zip ] && wget https://unlimited.dl.sourceforge.net/project/glew/glew/2.1.0/glew-2.1.0.zip
unzip glew-2.1.0.zip
cd glew-2.1.0
make all
mkdir -p ../lib ../inc
mv lib/libGLEW.a ../lib
cp -r include/GL ../inc
