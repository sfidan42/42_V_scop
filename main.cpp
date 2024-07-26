#include <main.hpp>

int	main(void)
{
	try
	{
		GLFWwindow		*window;
		unsigned int	indexSize;
		Shader			shader;

		/* Initialize the library */
		if (!glfwInit())
			throw std::runtime_error("Error: GLFW not initialized");
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
			throw std::runtime_error("Error: GLEW not initialized");
		/* Print OpenGL version */
		std::cout << glGetString(GL_VERSION) << std::endl;
		setVertexArray();
		indexSize = setVertexIndexArray();
		shader << "res/shaders/Basic.shader";
		shader.use();
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			/* Drawing */
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, nullptr);
			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			/* Poll for and process events */
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
}
