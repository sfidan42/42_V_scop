LDFLAGS	=	-framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
LDFLAGS	+=	-Llib -lglfw3 -lGLEW -Iinc
CPP		=	c++ -std=c++11 -Wall -Wextra -Werror
TARGET	=	run
GLEW	=	lib/libGLEW.a
GLFW	=	lib/libglfw3.a

all: $(TARGET)
	./$(TARGET)

$(GLEW):
	@echo "$(GLEW) not found, please install it"

$(GLFW):
	@echo "$(GLFW) not found, please install it"

$(TARGET): $(GLEW) $(GLFW) main.cpp
	$(CPP) main.cpp $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean all

.PHONY: all clean fclean re