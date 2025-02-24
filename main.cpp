#include <scop.hpp>

float			g_width = 800.0f;
float			g_height = 600.0f;
float			g_hStep = 0.0f;
float			g_vStep = 0.0f;
unsigned int	g_shaderProgram;

void	framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	g_width = width;
	g_height = height;
	glViewport(0, 0, g_width, g_height);
	std::cout << "width: " << g_width << " height: " << g_height << std::endl;

	glm::mat4	projection = glm::perspective(glm::radians(70.0f), g_width / g_height, 0.1f, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(g_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
			case GLFW_KEY_W: g_vStep += 0.01f; break;
			case GLFW_KEY_A: g_hStep -= 0.01f; break;
			case GLFW_KEY_S: g_vStep -= 0.01f; break;
			case GLFW_KEY_D: g_hStep += 0.01f; break;
			default: break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
			case GLFW_KEY_W: g_vStep = 0.0f; break;
			case GLFW_KEY_A: g_hStep = 0.0f; break;
			case GLFW_KEY_S: g_vStep = 0.0f; break;
			case GLFW_KEY_D: g_hStep = 0.0f; break;
			default: break;
		}
	}
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

	window = glfwCreateWindow(g_width, g_height, "scop", NULL, NULL);
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

	glViewport(0, 0, g_width, g_height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	std::string	path(av[1]);

	obj.read(path + ".obj", (path + ".mtl"));

	std::vector<float>			vertices = obj.getVertices();
	std::vector<unsigned int>	indices = obj.getIndices();
	tMaterial					mat = obj.getMaterial();

	unsigned int	VBO;
	unsigned int	VAOs;
	unsigned int	EBO;

	glGenVertexArrays(3, &VAOs);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAOs);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	float	distance = 0.0f;
	for (const auto& vertex : vertices)
	{
		distance = std::max(distance, std::abs(vertex));
	}
	distance = distance * 2.0f + (5.0f / 8.0f) * (cosf(35.0f) / sinf(35.0f));

	shader.parse("res/shaders/specular.shader");
	g_shaderProgram = shader.create();

	glm::mat4	model = glm::mat4(1.0f);
	glm::mat4	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -distance));
	glm::mat4	projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

	glUseProgram(g_shaderProgram);
	glUniform3f(glGetUniformLocation(g_shaderProgram, "lightPos"), distance, -distance, -distance);
	glUniform3f(glGetUniformLocation(g_shaderProgram, "ambientColor"), mat.ka.r, mat.ka.g, mat.ka.b);
	glUniform3f(glGetUniformLocation(g_shaderProgram, "diffuseColor"), mat.kd.r, mat.kd.g, mat.kd.b);
	glUniform3f(glGetUniformLocation(g_shaderProgram, "specularColor"), mat.ks.r, mat.ks.g, mat.ks.b);
	glUniformMatrix4fv(glGetUniformLocation(g_shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(g_shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(g_shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::rotate(model, glm::radians((float)M_PI / 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(g_shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

		view = glm::translate(view, glm::vec3(g_hStep * distance, g_vStep * distance, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(g_shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
