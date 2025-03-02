#include <Scop.hpp>

Scop::Scop(void)
{
    cameraPos = glm::vec3(0.0f, 0.0f,  0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
    model = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 20000.0f);
}

Scop::~Scop(void)
{
}

Shader	Scop::shader;
bool	Scop::texLoaded;

glm::vec3	Scop::cameraPos;
glm::vec3	Scop::cameraFront;
glm::vec3	Scop::cameraUp;
glm::mat4	model;
glm::mat4	view;
glm::mat4	projection;

float	Scop::deltaTime = 0.0f;
float	Scop::lastFrame = 0.0f;

float		Scop::speedCoeff;

glm::vec3	Scop::cameraSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraUpSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraDownSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraRightSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraLeftSpeed = glm::vec3(0.0f);

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

# define STB_IMAGE_IMPLEMENTATION
# include <stb_image.h>

void    Scop::loadTexture(const char *texPath)
{
	unsigned int	texture;

	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(texPath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		texLoaded = true;
	}
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
        texLoaded = false;
    }
}
