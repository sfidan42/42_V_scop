#include <scop.hpp>

int	main(void)
{
	try
	{
		GLFWwindow		*window;
		Shader			shader;

		/* Initialize the library */
		if (!glfwInit())
			throw std::runtime_error("Error: GLFW not initialized");
		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return (-1);
		}
		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		/* Enable V-Sync */
		glfwSwapInterval(1);
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Error: GLEW not initialized");
		/* Print OpenGL version */
		std::cout << glGetString(GL_VERSION) << std::endl;

		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

		IndexBuffer ib(indices, 6);

		/* Load the shader */
		shader << "res/shaders/Basic.shader";

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		/* Start using the shader before render loop */
		shader.use();

		/* Loop until the user closes the window */
		float r = 0.0f, increment = 0.05f;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			/* Drawing */
			shader.changeColor(r, .3f, .8f, 1.0f);

			GLCall(glBindVertexArray(vao));
			ib.bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;
			r += increment;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	glfwTerminate();
	return (0);
}
