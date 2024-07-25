SRC		=	CreateShader.cpp  ParseShader.cpp
OBJ		=	$(addprefix bin/, $(SRC:.cpp=.o))
NAME	=	libscop.a
EXE		=	scop
GLFW	=	lib/libglfw3.a
GLEW	=	lib/libGLEW.a
CC		=	c++ -Wall -Wextra -Werror -std=c++11 -Iinc

all: $(EXE)
	./$(EXE)

bin/%.o: src/%.cpp | bin
	${CC} -c $< -o $@

bin:
	mkdir -p bin

$(GLEW):
	./add_glew.sh

$(GLFW):
	./add_glfw.sh

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(EXE): main.cpp $(GLFW) $(GLEW) $(NAME)
	$(CC) main.cpp -L. -lscop -Llib -lGLEW -lglfw3 -lGL -o $(EXE)

clean:
	rm -rf $(NAME) $(EXE) bin

fclean: clean
	rm -f $(GLFW) $(GLEW)
	rm -rf inc/GLFW inc/GL glfw-3.4 glew-2.1.0

re: clean all

.PHONY: all bin clean fclean re