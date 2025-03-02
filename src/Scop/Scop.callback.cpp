#include <Scop.hpp>

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
			case GLFW_KEY_W: cameraUpSpeed = cameraFront; cameraSpeed += cameraUpSpeed; break;
			case GLFW_KEY_A: cameraLeftSpeed = glm::normalize(glm::cross(cameraFront, cameraUp)); cameraSpeed -= cameraLeftSpeed; break;
			case GLFW_KEY_S: cameraDownSpeed = cameraFront; cameraSpeed -= cameraDownSpeed; break;
			case GLFW_KEY_D: cameraRightSpeed = glm::normalize(glm::cross(cameraFront, cameraUp)); cameraSpeed += cameraRightSpeed; break;
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
