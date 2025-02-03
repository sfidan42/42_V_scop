SRC     =   error.cpp
OBJ     =   $(addprefix bin/, $(SRC:.cpp=.o))

EXE     =   scop

NAME    =   libscop.a
GLFW    =   dep/lib/src/libglfw3.a
GLAD    =   dep/lib/bin/glad.o

CXX     =   c++ -Wall -Wextra -Werror -std=c++11 -Iinc -Idep/lib/inc -g

FLAGS   =   -L. -lscop -Ldep/lib/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(EXE)
	./$(EXE) || echo "Error: $(EXE) failed"

bin/%.o: src/%.cpp
	$(CXX) -c $< -o $@

$(GLFW):
	make -C dep glfw

$(GLAD):
	make  -C dep glad

bin:
	mkdir -p bin

$(NAME): $(GLAD) bin $(OBJ)
	ar rcs $(NAME) $(OBJ) $(GLAD)

$(EXE): main.cpp $(GLFW) $(NAME)
	$(CXX) main.cpp $(FLAGS) -o $(EXE)

clean:
	rm -rf $(NAME) bin

fclean: clean
	rm -rf $(EXE)
	make -C dep clean

re: fclean all

.PHONY: all clean fclean re dep_glad dep_glfw