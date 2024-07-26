#include <main.h>

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

	const unsigned int	size = 12;
	const unsigned int	vertexSize = 2;
	float				data[size] = {
		 -.5f, -.5f,
		  .5f, -.5f,
		  .5f,  .5f,
		  -.5f,  .5f,
	};

	unsigned int	buffer_id;
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), 0);

	const unsigned int	indexSize = 6;
	unsigned int 		indices[indexSize] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int	ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	ShaderProgramSource	source = ParseShader("res/shaders/Basic.shader");
	GLuint	shader = CreateShader(source);
	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}
