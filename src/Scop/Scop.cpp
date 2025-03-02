#include <Scop.hpp>

float	Scop::vRotate = 0.0f;
float	Scop::hRotate = 0.0f;
Shader	Scop::shader;
bool	Scop::texLoaded;
glm::vec3	Scop::cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f);
glm::vec3	Scop::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3	Scop::cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float	Scop::deltaTime = 0.0f;
float	Scop::lastFrame = 0.0f;
glm::vec3	Scop::cameraSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraUpSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraDownSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraRightSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraLeftSpeed = glm::vec3(0.0f);
float		Scop::speedCoeff;

void	Scop::framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	(void)window;
	glViewport(0, 0, w, h);
	glm::mat4	projection = glm::perspective(glm::radians(70.0f), (float)w / (float)h, 0.1f, 20000.0f);
	shader.setMat4fv("projection", glm::value_ptr(projection));
}

void	Scop::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
			case GLFW_KEY_T: texLoaded = !texLoaded; texLoaded ? shader.use(1): shader.use(0); break;
			case GLFW_KEY_W: cameraUpSpeed = speedCoeff * deltaTime * cameraFront; cameraSpeed += cameraUpSpeed; break;
			case GLFW_KEY_A: cameraLeftSpeed = speedCoeff * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp)); cameraSpeed -= cameraLeftSpeed; break;
			case GLFW_KEY_S: cameraDownSpeed = speedCoeff * deltaTime * cameraFront; cameraSpeed -= cameraDownSpeed; break;
			case GLFW_KEY_D: cameraRightSpeed = speedCoeff * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp)); cameraSpeed += cameraRightSpeed; break;
			default: break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
			case GLFW_KEY_W: cameraSpeed -= cameraUpSpeed; break;
			case GLFW_KEY_A: cameraSpeed += cameraLeftSpeed; break;
			case GLFW_KEY_S: cameraSpeed += cameraDownSpeed; break;
			case GLFW_KEY_D: cameraSpeed -= cameraRightSpeed; break;
			default: break;
		}
	}
}