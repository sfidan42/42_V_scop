SRC		=	CreateShader.cpp  ParseShader.cpp
OBJ		=	$(addprefix bin/, $(SRC:.cpp=.o))
NAME	=	libscop.a
EXE		=	scop
GLFW	=	lib/libglfw3.a
GLEW	=	lib/libGLEW.a
CC		=	c++ -Wall -Wextra -Werror -std=c++11 -Iinc

all: $(GLFW) $(GLEW) $(NAME) compile run

bin/%.o: src/%.cpp | bin
	@echo "Compiling $<"
	${CC} -c $< -o $@

bin:
	mkdir -p bin

$(GLEW):
	./add_glew.sh

$(GLFW):
	./add_glfw.sh

$(NAME): $(OBJ)
	@echo "Creating $(NAME)"
	ar rcs $(NAME) $(OBJ)

compile: main.cpp
	@echo "Compiling $(EXE)"
	$(CC) main.cpp -L. -lscop -Llib -lGLEW -lglfw3 -lGL -o $(EXE)

run:
	@echo "Running $(EXE)"
	./$(EXE)

clean:
	rm -rf $(NAME) $(EXE) bin

fclean: clean
	rm -f $(GLFW) $(GLEW)
	rm -rf inc/GLFW inc/GL glfw-3.4 glew-2.1.0

re: clean all

.PHONY: all bin compile run clean fclean re