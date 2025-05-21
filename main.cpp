#include <Scop.hpp>

int	main(int c, char **av)
{
	GLFWwindow		*window;
	Scop			scop;
	WavefrontObj	obj;

	if (c != 4)
	{
		cerr << "usage: ./program [.obj] [.mtl] [.{png, jpg}]" << endl;
		return (-1);
	}

	if (!glfwInit())
		return (-1);

	window = glfwCreateWindow(800, 600, "scop", NULL, NULL);
	if (!window)
	{
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return (-1);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "Failed to initialize GLAD" << endl;
		return (-1);
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, Scop::framebuffer_size_callback);
	glfwSetKeyCallback(window, Scop::key_callback);
	glfwSetMouseButtonCallback(window, Scop::mouse_button_callback);
	glfwSetCursorPosCallback(window, Scop::mouse_callback);

	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;

	obj.read(av[1], av[2]);

	vector<float>			vertices = obj.getVertices();
	vector<unsigned int>	indices = obj.getIndices();
	tMaterial				material = obj.getMaterial();

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
		distance = max(distance, abs(vertex));
	}	
	vec3	camLoc = vec3(0.0f, 0.0f, distance * 2.0f + (5.0f / 8.0f) * (cosf(35.0f) / sinf(35.0f)));
	vec3	lightPos = vec3(distance, -distance, -distance);

	scop.locateCamera(camLoc);
	scop.setSpeedCoeff(distance * 10.0f);

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

	vec3	clColor = material.ka;

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
	return (0);
}
