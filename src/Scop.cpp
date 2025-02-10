#include <Scop.hpp>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
float firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void	framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;
	
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void	processInput(GLFWwindow *window, unsigned int shaderProgram)
{
	static float mixValue = 0.2f;

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		if(mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		if(mixValue <= 0.0f)
			mixValue = 0.0f;
	}
	glUniform1f(glGetUniformLocation(shaderProgram, "mixValue"), mixValue);

	float	cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void	transform(unsigned int shaderProgram, unsigned int i, glm::vec3 cubePositions[10], float angle_ratio)
{

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glm::mat4	view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, cubePositions[i]);
	float angle = 20.0f * (i + 1) * angle_ratio;
	model = glm::rotate(model, glm::radians(angle),
	glm::vec3(1.0f, 0.3f, 0.5f));

	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}
