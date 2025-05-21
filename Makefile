SRC     =   error.cpp \
			$(addprefix Shader/, Shader.cpp Shader.set.cpp) \
			$(addprefix Scop/, Scop.cpp Scop.load.cpp Scop.callback.cpp Scop.set.cpp) \
			$(addprefix WavefrontObj/, WavefrontObj.cpp WavefrontObj.read.cpp WavefrontObj.get.cpp) \

OBJ     =   $(addprefix bin/, $(SRC:.cpp=.o))

HDR		=	$(addprefix inc/, Scop.hpp Shader.hpp WavefrontObj.hpp error.h)
HDR		+=	$(addprefix inc/glm2/, vec.hpp mat.hpp vec.inl mat.inl transform.hpp)

EXE     =   scop

NAME    =   libscop.a

GLFW    =   dep/lib/src/libglfw3.a
GLAD    =   dep/lib/bin/glad.o
STB		=   dep/lib/inc/stb_image.h

CXX     =   c++ -Wall -Wextra -std=c++20 -Iinc -Idep/lib/inc -g

FLAGS   =   -L. -lscop -Ldep/lib/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(STB) $(GLAD) $(GLFW) $(EXE)
	@echo "______________face__________________"
	@./$(EXE) res/objects/face.obj "" ""			|| echo "Error: $(EXE) failed"
	@echo "______________cube__________________"
	@./$(EXE) res/objects/cube.obj "" ""			|| echo "Error: $(EXE) failed"
	@echo "_______________42___________________"
	@./$(EXE) res/objects/42.obj \
				res/materials/42.mtl \
				""								|| echo "Error: $(EXE) failed"
	@echo "_____________capsule________________"
	@./$(EXE) res/objects/capsule.obj \
			res/materials/capsule.mtl \
			res/textures/capsule.jpg			|| echo "Error: $(EXE) failed"
	@echo "_____________teapot_________________"
	@./$(EXE) res/objects/teapot.obj ""	""		|| echo "Error: $(EXE) failed"
	@echo "_____________teapot2________________"
	@./$(EXE) res/objects/teapot2.obj \
		res/materials/teapot2.mtl \
		""									|| echo "Error: $(EXE) failed"
	@echo "____________max-planck______________"
	@./$(EXE) res/objects/max-planck.obj "" ""	|| echo "Error: $(EXE) failed"

bin/%.o: src/%.cpp $(HDR)
	$(CXX) -c $< -o $@

bin:
	mkdir -p $(addprefix bin/, WavefrontObj Shader Scop)

$(GLFW):
	make -C dep glfw
$(GLAD):
	make -C dep glad
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
