SRC     =   error.cpp Shader.cpp Scop.cpp Obj.cpp
OBJ     =   $(addprefix bin/, $(SRC:.cpp=.o))

EXE     =   scop

NAME    =   libscop.a

GLFW    =   dep/lib/src/libglfw3.a
GLAD    =   dep/lib/bin/glad.o
GLM		=   dep/lib/inc/glm/glm.hpp
STB		=   dep/lib/inc/stb_image.h

CXX     =   c++ -Wall -Wextra -Werror -std=c++11 -Iinc -Idep/lib/inc -g -lm

FLAGS   =   -L. -lscop -Ldep/lib/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(STB) $(GLM) $(GLAD) $(GLFW) $(EXE)
	./$(EXE) || echo "Error: $(EXE) failed"

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
$(STB):
	make -C dep stb

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
