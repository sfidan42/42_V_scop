NAME	=	viewer
GLFW	=	lib/libglfw3.a
CC		=	c++ -Wall -Wextra -Werror -std=c++11

all: $(GLFW) $(NAME) run

$(GLFW):
	./add_glfw.sh

$(NAME): main.cpp
	$(CC) main.cpp -Iinc -Llib -lglfw3 -lGL -o $(NAME)

run:
	./$(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(GLFW)
	rm -rf inc/GLFW
	rm -rf glfw-3.4

re: clean all

.PHONY: all run clean fclean re