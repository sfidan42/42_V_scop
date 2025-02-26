#include <scop.hpp>

float	g_hStep = 0.0f;
float	g_vStep = 0.0f;
float	g_vRotate = 0.0f;
float	g_hRotate = 0.0f;
Shader	shader;
bool	g_texLoaded;
tColor	g_clearColor;

void	framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	(void)window;
	glViewport(0, 0, w, h);
	glm::mat4	projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.1f, 20000.0f);
	shader.setMat4fv("projection", glm::value_ptr(projection));
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
			case GLFW_KEY_W: g_vStep += 0.015f; break;
			case GLFW_KEY_A: g_hStep -= 0.015f; break;
			case GLFW_KEY_S: g_vStep -= 0.015f; break;
			case GLFW_KEY_D: g_hStep += 0.015f; break;
			case GLFW_KEY_LEFT: g_vRotate -= M_PI / 5.0f; break;
			case GLFW_KEY_RIGHT: g_vRotate += M_PI / 5.0f; break;
			case GLFW_KEY_UP: g_hRotate += M_PI / 5.0f; break;
			case GLFW_KEY_DOWN: g_hRotate -= M_PI / 5.0f; break;
			case GLFW_KEY_T: g_texLoaded = !g_texLoaded; g_texLoaded ? shader.use(1): shader.use(0); break;
			default: break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
			case GLFW_KEY_W: g_vStep -= 0.015f; break;
			case GLFW_KEY_A: g_hStep += 0.015f; break;
			case GLFW_KEY_S: g_vStep += 0.015f; break;
			case GLFW_KEY_D: g_hStep -= 0.015f; break;
			case GLFW_KEY_LEFT: g_vRotate += M_PI / 5.0f; break;
			case GLFW_KEY_RIGHT: g_vRotate -= M_PI / 5.0f; break;
			case GLFW_KEY_UP: g_hRotate -= M_PI / 5.0f; break;
			case GLFW_KEY_DOWN: g_hRotate += M_PI / 5.0f; break;
			default: break;
		}
	}
}

int	main(int c, char **av)
{
	GLFWwindow	*window;
	Obj			obj;

	if (c != 4)
	{
		std::cerr << "usage: ./program [.obj] [.mtl] [.{png, jpg}]" << std::endl;
		return (-1);
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

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	obj.read(av[1], av[2]);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	float	distance = 0.0f;
	for (const auto& vertex : vertices)
	{
		distance = std::max(distance, std::abs(vertex));
	}
	distance = distance * 2.0f + (5.0f / 8.0f) * (cosf(35.0f) / sinf(35.0f));

	shader.read("res/shaders/specular.shader");
	shader.read("res/shaders/specular.textured.shader");
	shader.create();

	glm::mat4	model = glm::mat4(1.0f);
	glm::mat4	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -distance));
	glm::mat4	projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 20000.0f);

	g_texLoaded = loadTexture(av[3]);

	shader.use(0);
	shader.set3f("lightPos", distance, -distance, -distance);
	shader.set3f("ambientColor", mat.ka.r, mat.ka.g, mat.ka.b);
	shader.set3f("diffuseColor", mat.kd.r, mat.kd.g, mat.kd.b);
	shader.set3f("specularColor", mat.ks.r, mat.ks.g, mat.ks.b);
	shader.setMat4fv("model", glm::value_ptr(model));
	shader.setMat4fv("view", glm::value_ptr(view));
	shader.setMat4fv("projection", glm::value_ptr(projection));

	shader.use(1);
	shader.set3f("lightPos", distance, -distance, -distance);
	shader.set3f("ambientColor", mat.ka.r, mat.ka.g, mat.ka.b);
	shader.set3f("diffuseColor", mat.kd.r, mat.kd.g, mat.kd.b);
	shader.set3f("specularColor", mat.ks.r, mat.ks.g, mat.ks.b);
	shader.setMat4fv("model", glm::value_ptr(model));
	shader.setMat4fv("view", glm::value_ptr(view));
	shader.setMat4fv("projection", glm::value_ptr(projection));

	g_texLoaded ? shader.use(1) : shader.use(0);

	glBindVertexArray(VAOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(mat.ka.r, mat.ka.g, mat.ka.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::rotate(model, glm::radians(g_vRotate), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setMat4fv("model", glm::value_ptr(model));

		view = glm::translate(view, glm::vec3(g_hStep * distance, g_vStep * distance, 0.0f));
		shader.setMat4fv("view", glm::value_ptr(view));

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
