NAME	=	viewer
GLFW	=	lib/libglfw3.a
GLEW	=	lib/libGLEW.a
CC		=	c++ -Wall -Wextra -Werror -std=c++11

all: $(GLFW) $(GLEW) $(NAME) run

$(GLEW):
	./add_glew.sh

$(GLFW):
	./add_glfw.sh

$(NAME): main.cpp
	$(CC) main.cpp -Iinc -Llib -lGLEW -lglfw3 -lGL -o $(NAME)

run:
	./$(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(GLFW) $(GLEW)
	rm -rf inc/GLFW inc/GL
	rm -rf glfw-3.4 glew-2.1.0

re: clean all

.PHONY: all run clean fclean re