SRC     =   error.cpp Shader.cpp Obj.cpp Vertex.cpp
OBJ     =   $(addprefix bin/, $(SRC:.cpp=.o))

EXE     =   scop

NAME    =   libscop.a

GLFW    =   dep/lib/src/libglfw3.a
GLAD    =   dep/lib/bin/glad.o
GLM		=   dep/lib/inc/glm/glm.hpp

CXX     =   c++ -Wall -Wextra -Werror -std=c++11 -Iinc -Idep/lib/inc -g -lm

FLAGS   =   -L. -lscop -Ldep/lib/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(STB) $(GLM) $(GLAD) $(GLFW) $(EXE)
	./$(EXE) res/objects/42 || echo "Error: $(EXE) failed"

bin/%.o: src/%.cpp
	$(CXX) -c $< -o $@

bin:
	mkdir -p bin

$(GLFW):
	make -C dep glfw
$(GLAD):
	make -C dep glad
$(GLM):
	make -C dep glm

$(NAME): bin $(OBJ)
	ar rcs $(NAME) $(OBJ) $(GLAD)

$(EXE): main.cpp $(NAME)
	$(CXX) main.cpp $(FLAGS) -o $(EXE)

clean:
	rm -rf $(NAME) bin

fclean: clean
	rm -rf $(EXE)
	make -C dep clean

re: fclean all

.PHONY: all clean fclean re
