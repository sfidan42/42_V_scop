SRC		=	Shader.cpp VertexBuffer.cpp IndexBuffer.cpp error.cpp
OBJ		=	$(addprefix bin/, $(SRC:.cpp=.o))
NAME	=	libscop.a
EXE		=	scop
GLFW	=	lib/libglfw3.a
GLEW	=	lib/libGLEW.a
CC		=	c++ -Wall -Wextra -Werror -std=c++11 -Iinc #-g
LIBS	=	-L. -lscop -Llib -lGLEW -lglfw3
FRAMES	=	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

all: $(EXE)
	./$(EXE) || echo "Error: $(EXE) failed"

bin/%.o: src/%.cpp
	${CC} -c $< -o $@

$(GLEW):
	@echo $(GLEW) is required to build $(EXE)
	exit 1

$(GLFW):
	@echo $(GLFW) is required to build $(EXE)
	exit 1

bin:
	mkdir -p bin

$(NAME): bin $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(EXE): main.cpp $(GLFW) $(GLEW) $(NAME)
	$(CC) main.cpp $(LIBS) $(FRAMES) -o $(EXE)

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME) $(EXE)
re: fclean all

.PHONY: all clean fclean re