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

	unsigned int		buffer_id;
	const unsigned int	size = 10;
	float				data[size] = {
		 .0f, .0f,
		 .0f, .5f,
		 .5f, .5f,
		 .5f, .0f,
		-.5, -.5f,
	};

	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_LINE_LOOP, 0, 5);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
