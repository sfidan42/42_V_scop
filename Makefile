SRC     =   error.cpp \
			Scop/Scop.cpp Scop/Scop.load.cpp Scop/Scop.callback.cpp Scop/Scop.set.cpp \
			Shader/Shader.cpp Shader/Shader.set.cpp \
			WavefrontObj/WavefrontObj.cpp WavefrontObj/WavefrontObj.read.cpp WavefrontObj/WavefrontObj.get.cpp
OBJ     =   $(addprefix bin/, $(SRC:.cpp=.o))
HDR		=	$(addprefix inc/, Scop.hpp Shader.hpp WavefrontObj.hpp error.h)
HDR		+=	$(addprefix inc/, glm2/vec.hpp glm2/mat.hpp glm2/vec.inl glm2/mat.inl glm2/transform.hpp)

EXE     =   scop

NAME    =   libscop.a

GLFW    =   dep/lib/src/libglfw3.a
GLAD    =   dep/lib/bin/glad.o
GLM		=   dep/lib/inc/glm/glm.hpp
STB		=   dep/lib/inc/stb_image.h

CXX     =   c++ -Wall -Wextra -std=c++20 -Iinc -Idep/lib/inc -g -lm

FLAGS   =   -L. -lscop -Ldep/lib/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(STB) $(GLM) $(GLAD) $(GLFW) $(EXE)
#	@echo "______________face__________________"
#	@./$(EXE) res/objects/face.obj "" ""			|| echo "Error: $(EXE) failed"
#	@echo "______________cube__________________"
#	@./$(EXE) res/objects/cube.obj "" ""			|| echo "Error: $(EXE) failed"
	@echo "_______________42___________________"
	@./$(EXE) res/objects/42.obj \
				res/materials/42.mtl \
				""								|| echo "Error: $(EXE) failed"
#	@echo "_____________capsule________________"
#	@./$(EXE) res/objects/capsule.obj \
#			res/materials/capsule.mtl \
#			res/textures/capsule.jpg			|| echo "Error: $(EXE) failed"
#	@echo "_____________teapot_________________"
#	@./$(EXE) res/objects/teapot.obj ""	""		|| echo "Error: $(EXE) failed"
	@echo "_____________teapot2________________"
	@./$(EXE) res/objects/teapot2.obj \
			res/objects/teapot2.mtl \
			""									|| echo "Error: $(EXE) failed"
#	@echo "____________max-planck______________"
#	@./$(EXE) res/objects/max-planck.obj "" ""	|| echo "Error: $(EXE) failed"

bin/%.o: src/%.cpp $(HDR)
	$(CXX) -c $< -o $@

bin:
	mkdir -p bin/WavefrontObj bin/Shader bin/Scop

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
