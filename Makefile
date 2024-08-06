SRC		=	Shader.cpp VertexBuffer.cpp IndexBuffer.cpp error.cpp
OBJ		=	$(addprefix bin/, $(SRC:.cpp=.o))
NAME	=	libscop.a
EXE		=	scop
GLFW	=	lib/libglfw3.a
GLEW	=	lib/libGLEW.a
CC		=	c++ -Wall -Wextra -Werror -std=c++11 -Iinc -g

all: $(EXE)
	./$(EXE) || echo "Error: $(EXE) failed"

bin/%.o: src/%.cpp
	${CC} -c $< -o $@

bin:
	mkdir -p bin

$(GLEW):
	./add_glew.sh

$(GLFW):
	./add_glfw.sh

$(NAME): bin $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(EXE): main.cpp $(GLFW) $(GLEW) $(NAME)
	$(CC) main.cpp -L. -lscop -Llib -lGLEW -lglfw3 -lGL -o $(EXE)

clean:
	rm -rf $(NAME) $(EXE) bin

fclean: clean
	rm -f $(GLFW) $(GLEW)
	rm -rf inc/GLFW inc/GL
	rm -rf glfw-3.4 glew-2.1.0

re: fclean all

.PHONY: all clean fclean re