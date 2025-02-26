SRC     =   error.cpp Vertex.cpp texture.cpp \
			Shader.cpp Shader.set.cpp \
			Obj.cpp Obj.read.cpp Obj.get.cpp
OBJ     =   $(addprefix bin/, $(SRC:.cpp=.o))

EXE     =   scop

NAME    =   libscop.a

GLFW    =   dep/lib/src/libglfw3.a
GLAD    =   dep/lib/bin/glad.o
GLM		=   dep/lib/inc/glm/glm.hpp
STB		=   dep/lib/inc/stb_image.h

CXX     =   c++ -Wall -Wextra -std=c++20 -Iinc -Idep/lib/inc -g -lm

FLAGS   =   -L. -lscop -Ldep/lib/src -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(STB) $(GLM) $(GLAD) $(GLFW) $(EXE)
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
			res/objects/teapot2.mtl \
			""									|| echo "Error: $(EXE) failed"
	@echo "____________max-planck______________"
	@./$(EXE) res/objects/max-planck.obj "" ""	|| echo "Error: $(EXE) failed"
	@echo "______________Flower________________"
	@./$(EXE) res/objects/other/Flower.obj \
			res/objects/other/Flower.mtl \
			res/objects/other/Flower.jpg				|| echo "Error: $(EXE) failed"
	@echo "___________Chinese Coin_____________"
	@./$(EXE) res/objects/other/chinese_coin.obj \
			res/objects/other/chinese_coin.mtl \
			res/objects/other/chinese_coin.jpg		|| echo "Error: $(EXE) failed"
	@echo "______________Helmet_________________"
	@./$(EXE) res/objects/other/Helmet.obj \
			res/objects/other/Helmet.mtl \
			res/objects/other/Helmet_1.png		|| echo "Error: $(EXE) failed"
	@echo "______________Axe_________________"
	@./$(EXE) res/objects/other/Axe.obj \
			res/objects/other/Axe.mtl \
			res/objects/other/Axe_1.png		|| echo "Error: $(EXE) failed"
	@echo "______________Classic side table_________________"
	@./$(EXE) res/objects/other/Classic\ side\ table.obj \
			res/objects/other/Classic\ side\ table.mtl \
			res/objects/other/Classic\ side\ table_0.jpg		|| echo "Error: $(EXE) failed"
	@echo "______________Stanley Screwdriver-obj_________________"
	@./$(EXE) res/objects/other/Stanley\ Screwdriver-obj.obj \
			res/objects/other/Stanley\ Screwdriver-obj.mtl \
			res/objects/other/Stanley\ Screwdriver-obj_0.jpg		|| echo "Error: $(EXE) failed"
	@echo "______________Fountain_________________"
	@./$(EXE) res/objects/other/Fountain.obj \
			res/objects/other/Fountain.mtl \
			res/objects/other/Fountain_0.png		|| echo "Error: $(EXE) failed"

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
