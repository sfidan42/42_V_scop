#include <Scop.hpp>

int	main(int c, char **av)
{
	glm2::mat4	mat(1.0f);

	glm::mat4	mat2(1.0f);

	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			std::cout << mat2[i][j] << " ";
		}
		std::cout << std::endl;
	}

	GLFWwindow		*window;
	WavefrontObj	obj;
	Scop			scop;

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

	glfwSetFramebufferSizeCallback(window, Scop::framebuffer_size_callback);
	glfwSetKeyCallback(window, Scop::key_callback);
	glfwSetMouseButtonCallback(window, Scop::mouse_button_callback);
	glfwSetCursorPosCallback(window, Scop::mouse_callback);

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	obj.read(av[1], av[2]);

	std::vector<float>			vertices = obj.getVertices();
	std::vector<unsigned int>	indices = obj.getIndices();
	tMaterial					material = obj.getMaterial();

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
	glm::vec3	camLoc = glm::vec3(0.0f, 0.0f, distance * 2.0f + (5.0f / 8.0f) * (cosf(35.0f) / sinf(35.0f)));
	glm::vec3	lightPos = glm::vec3(distance, -distance, -distance);

	scop.locateCamera(camLoc);
	scop.setSpeedCoeff(distance * 5.0f);

	scop.loadTexture(av[3]);

	Scop::shader.config(2);

	Scop::shader.read("res/shaders/specular.shader");
	Scop::shader.read("res/shaders/specular.textured.shader");
	Scop::shader.create();

	Scop::shader.use(0);
	scop.setLightPos(lightPos);
	scop.setMaterial(material);
	scop.setMVP();

	Scop::shader.use(1);
	scop.setLightPos(lightPos);
	scop.setMaterial(material);
	scop.setMVP();

	scop.useShader();

	glBindVertexArray(VAOs);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glEnable(GL_DEPTH_TEST);

	glm::vec3	clColor = material.ka;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(clColor.x, clColor.y, clColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scop.calcDeltaTime();
		scop.transformObject();
		scop.moveCamera();

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
