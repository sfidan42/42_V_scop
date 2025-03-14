#include <Scop.hpp>

void	Scop::framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glm2::mat4	projection;

	(void)window;
	glViewport(0, 0, w, h);
	projection = glm2::perspective(glm2::radians(70.0f), (float)w / (float)h, 0.1f, 20000.0f);
	shader.setMat4fv("projection", glm2::value_ptr(projection));
}

void	Scop::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true);
				break;
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
			case GLFW_KEY_T:	texLoaded = !texLoaded; texLoaded ? shader.use(1): shader.use(0);
				break;
			case GLFW_KEY_W:	cameraSpeeds[UP] = cameraUp;
								cameraSpeed -= cameraSpeeds[UP];
				break;
			case GLFW_KEY_A:	cameraSpeeds[LEFT] = glm2::normalize(glm2::cross(cameraFront, cameraUp));
								cameraSpeed += cameraSpeeds[LEFT];
				break;
			case GLFW_KEY_S:	cameraSpeeds[DOWN] = cameraUp;
								cameraSpeed += cameraSpeeds[DOWN];
				break;
			case GLFW_KEY_D:	cameraSpeeds[RIGHT] = glm2::normalize(glm2::cross(cameraFront, cameraUp)); 
								cameraSpeed -= cameraSpeeds[RIGHT];
				break;
			case GLFW_KEY_X:	cameraSpeeds[FRONT] = cameraFront;
								cameraSpeed -= cameraSpeeds[FRONT];
				break;
			case GLFW_KEY_Z:	cameraSpeeds[BACKWARD] = cameraFront;
								cameraSpeed += cameraSpeeds[BACKWARD];
				break;
			case GLFW_KEY_UP:	rotation = Rotation::PITCH_PLUS;	break;
			case GLFW_KEY_DOWN:	rotation = Rotation::PITCH_MINUS;	break;
			case GLFW_KEY_RIGHT:rotation = Rotation::YAW_PLUS;		break;
			case GLFW_KEY_LEFT:	rotation = Rotation::YAW_MINUS;		break;
			case GLFW_KEY_N:	rotation = Rotation::ROLL_PLUS;		break;
			case GLFW_KEY_M:	rotation = Rotation::ROLL_MINUS;	break;
			default: break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
			case GLFW_KEY_W: cameraSpeed += cameraSpeeds[UP]; break;
			case GLFW_KEY_A: cameraSpeed -= cameraSpeeds[LEFT]; break;
			case GLFW_KEY_S: cameraSpeed -= cameraSpeeds[DOWN]; break;
			case GLFW_KEY_D: cameraSpeed += cameraSpeeds[RIGHT]; break;
			case GLFW_KEY_X: cameraSpeed += cameraSpeeds[FRONT]; break;
			case GLFW_KEY_Z: cameraSpeed -= cameraSpeeds[BACKWARD]; break;
			case GLFW_KEY_UP:	rotation = Rotation::NONE; break;
			case GLFW_KEY_DOWN:	rotation = Rotation::NONE; break;
			case GLFW_KEY_RIGHT:rotation = Rotation::NONE; break;
			case GLFW_KEY_LEFT:	rotation = Rotation::NONE; break;
			case GLFW_KEY_N:	rotation = Rotation::NONE; break;
			case GLFW_KEY_M:	rotation = Rotation::NONE; break;
			default: break;
		}
	}
}

void	Scop::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	(void)mods;
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
				leftButtonPressed = !leftButtonPressed;
				firstMouse = true;
				if (leftButtonPressed)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				else
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			default: break;
		}
	}
}

void Scop::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void)window;

    if (leftButtonPressed)
    {
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

        float sensitivity = 0.5f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm2::vec3 direction;
        direction.x = cos(glm2::radians(yaw)) * cos(glm2::radians(pitch));
        direction.y = sin(glm2::radians(pitch));
        direction.z = sin(glm2::radians(yaw)) * cos(glm2::radians(pitch));

        cameraFront = glm2::normalize(direction);

        // Calculate the Right and Up vectors
        glm2::vec3 worldUp = glm2::vec3(0.0f, 1.0f, 0.0f);
        glm2::vec3 cameraRight = glm2::normalize(glm2::cross(cameraFront, worldUp));
        cameraUp = glm2::normalize(glm2::cross(cameraRight, cameraFront));
    }
}
