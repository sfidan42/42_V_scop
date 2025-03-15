#include <Scop.hpp>

void	Scop::framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	mat4	projection;

	(void)window;
	glViewport(0, 0, w, h);
	projection = perspective(radians(70.0f), (float)w / (float)h, 0.1f, 20000.0f);
	shader.setMat4fv("projection", value_ptr(projection));
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
			case GLFW_KEY_T: texLoaded = !texLoaded; texLoaded ? shader.use(1): shader.use(0); break;
			case GLFW_KEY_W:
				cameraSpeeds[eCameraSpeed::UP] = cameraUp; 
				cameraSpeed -= cameraSpeeds[eCameraSpeed::UP];
				break;
			case GLFW_KEY_A:
				cameraSpeeds[eCameraSpeed::LEFT] = normalize(cross(cameraFront, cameraUp));
				cameraSpeed += cameraSpeeds[eCameraSpeed::LEFT];
				break;
			case GLFW_KEY_S:
				cameraSpeeds[eCameraSpeed::DOWN] = cameraUp;
				cameraSpeed += cameraSpeeds[eCameraSpeed::DOWN];
				break;
			case GLFW_KEY_D:
				cameraSpeeds[eCameraSpeed::RIGHT] = normalize(cross(cameraFront, cameraUp));
				cameraSpeed -= cameraSpeeds[eCameraSpeed::RIGHT];
				break;
			case GLFW_KEY_X:
				cameraSpeeds[eCameraSpeed::FORWARD] = cameraFront;
				cameraSpeed -= cameraSpeeds[eCameraSpeed::FORWARD];
				break;
			case GLFW_KEY_Z:
				cameraSpeeds[eCameraSpeed::BACKWARD] = cameraFront;
				cameraSpeed += cameraSpeeds[eCameraSpeed::BACKWARD];
				break;
			case GLFW_KEY_UP: rotationDegree += 20.0f; rotationAxis.x -= 1.0f; break;
			case GLFW_KEY_DOWN: rotationDegree += 20.0f; rotationAxis.x += 1.0f; break;
			case GLFW_KEY_LEFT: rotationDegree += 20.0f; rotationAxis.y -= 1.0f; break;
			case GLFW_KEY_RIGHT: rotationDegree += 20.0f; rotationAxis.y += 1.0f; break;
			case GLFW_KEY_M: rotationDegree += 20.0f; rotationAxis.z -= 1.0f; break;
			case GLFW_KEY_N: rotationDegree += 20.0f; rotationAxis.z += 1.0f; break;
			default: break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_P: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	break;
			case GLFW_KEY_W: cameraSpeed += cameraSpeeds[eCameraSpeed::UP]; break;
			case GLFW_KEY_A: cameraSpeed -= cameraSpeeds[eCameraSpeed::LEFT]; break;
			case GLFW_KEY_S: cameraSpeed -= cameraSpeeds[eCameraSpeed::DOWN]; break;
			case GLFW_KEY_D: cameraSpeed += cameraSpeeds[eCameraSpeed::RIGHT]; break;
			case GLFW_KEY_X: cameraSpeed += cameraSpeeds[eCameraSpeed::FORWARD]; break;
			case GLFW_KEY_Z: cameraSpeed -= cameraSpeeds[eCameraSpeed::BACKWARD]; break;
			case GLFW_KEY_UP: rotationDegree -= 20.0f; rotationAxis.x += 1.0f; break;
			case GLFW_KEY_DOWN: rotationDegree -= 20.0f; rotationAxis.x -= 1.0f; break;
			case GLFW_KEY_LEFT: rotationDegree -= 20.0f; rotationAxis.y += 1.0f; break;
			case GLFW_KEY_RIGHT: rotationDegree -= 20.0f; rotationAxis.y -= 1.0f; break;
			case GLFW_KEY_M: rotationDegree -= 20.0f; rotationAxis.z += 1.0f; break;
			case GLFW_KEY_N: rotationDegree -= 20.0f; rotationAxis.z -= 1.0f; break;
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

        vec3 direction;
        direction.x = cos(radians(yaw)) * cos(radians(pitch));
        direction.y = sin(radians(pitch));
        direction.z = sin(radians(yaw)) * cos(radians(pitch));

        cameraFront = normalize(direction);

        // Calculate the Right and Up vectors
        vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
        vec3 cameraRight = normalize(cross(cameraFront, worldUp));
        cameraUp = normalize(cross(cameraRight, cameraFront));
    }
}
