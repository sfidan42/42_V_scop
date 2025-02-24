#include <scop.hpp>

float	g_window_width = 800.0f;
float	g_window_height = 600.0f;

void	framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	g_window_width = width;
	g_window_height = height;
	glViewport(0, 0, width, height);
}

void	processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void	setMVP(unsigned int shaderProgram, float distance)
{
	float angle = 180.0f * sinf(glfwGetTime());

	glm::mat4	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4	view = glm::mat4(1.0f);
	// note that we’re translating the scene in the reverse and up direction
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -distance));

	glm::mat4	projection;
	projection = glm::perspective(glm::radians(70.0f), g_window_width / g_window_height, 0.1f, 1000.0f);

	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

int	main(int c, char **av)
{
	GLFWwindow	*window;
	Shader		shader;
	Obj			obj;

	if (c != 2)
	{
		std::cerr << "provide a file (present it without .obj in its path)" << std::endl;
		return (1);
	}

	if (!glfwInit())
		return (-1);

	window = glfwCreateWindow(800, 600, "scop", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return (-1);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return (-1);
	}

	glViewport(0, 0, g_window_width, g_window_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	std::string				path(av[1]);

	obj.read(path + ".obj", (path + ".mtl"));
	
	std::vector<float>			vertices = obj.getVertices();
	std::vector<unsigned int>	indices = obj.getIndices();
	tMaterial					mat = obj.getMaterial();

	unsigned int	VBO;
	unsigned int	VAOs[2];
	unsigned int	EBO;

	glGenVertexArrays(3, VAOs);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(*VAOs);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	float		distance = 0.0f;
	for (const auto& vertex : vertices)
	{
		distance = std::max(distance, std::abs(vertex));
	}
	distance *= 2.0f;

	shader.parse("res/shaders/specular.shader");
	unsigned int	shaderProgram = shader.create();

	glUseProgram(shaderProgram);
	glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), distance, -distance, -distance);
	glUniform3f(glGetUniformLocation(shaderProgram, "ambientColor"), mat.ka.r, mat.ka.g, mat.ka.b);
	glUniform3f(glGetUniformLocation(shaderProgram, "diffuseColor"), mat.kd.r, mat.kd.g, mat.kd.b);
	glUniform3f(glGetUniformLocation(shaderProgram, "specularColor"), mat.ks.r, mat.ks.g, mat.ks.b);

	

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		processInput(window);

		setMVP(shaderProgram, distance);
		glBindVertexArray(*VAOs);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}
