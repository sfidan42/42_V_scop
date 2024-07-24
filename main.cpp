#include <main.h>

static
unsigned int	CompileShader(GLenum type, const std::string &source)
{
	GLuint		id;
	const char	*src;
	GLint		result;

	id = glCreateShader(type);
	src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint	length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char	*message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cerr << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static
GLuint	CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
	GLuint	program;
	GLuint	vs;
	GLuint	fs;

	program = glCreateProgram();
	vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int	main(void)
{
	GLFWwindow	*window;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cerr << "Error: GLFW not initialized" << std::endl;
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error: GLEW not initialized" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	unsigned int		buffer_id;
	const unsigned int	size = 10;
	float				data[size] = {
		 .0f, .0f,
		 .0f, .5f,
		 .5f, .5f,
		 .5f, .0f,
		-.1, -.1f,
	};

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	std::string	vertexShader = 
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";
	
	std::string	fragmentShader = 
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	GLuint	shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINES, 3, 2);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
