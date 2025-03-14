
CC		=	gcc -Wall -Wextra -Werror -std=c11 -g -Ilib/inc
GLAD	=	lib/bin/glad.o
GLFW	=	lib/src/libglfw3.a
STB		=	lib/inc/stb_image.h

all: glfw glad glm stb

prepare:
	mkdir -p lib/src lib/inc lib/bin

# glfw-3.4.zip: https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip

glfw: prepare $(GLFW)
glad: prepare $(GLAD)
stb: prepare $(STB)

$(GLFW):
	unzip glfw-3.4.zip
	cmake -S glfw-3.4 -B glfw-3.4/build
	make -C glfw-3.4/build
	mv glfw-3.4/include/GLFW lib/inc
	mv glfw-3.4/build/src/libglfw3.a lib/src
	rm -rf glfw-3.4

$(GLAD):
	unzip glad.zip
	mv glad/include/glad lib/inc
	mv glad/include/KHR lib/inc
	$(CC) -c glad/src/glad.c -o lib/bin/glad.o
	rm -rf glad

$(STB):
	cp stb_image.h lib/inc

clean:
	rm -rf lib glfw-3.4 glad

.PHONY: all glfw glad stb clean prepare
