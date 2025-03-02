#include <Scop.hpp>

Scop::Scop(void)
{
	model = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 20000.0f);
	speedCoeff = 0.0f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

Scop::~Scop(void)
{
}

void	Scop::moveCamera(glm::vec3 speed)
{
	if (speedCoeff == 0.0f)
		std::cout << "Speed coefficient not set" << std::endl;

	cameraPos += speed * speedCoeff * deltaTime;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4fv("view", glm::value_ptr(view));
}

void	Scop::locateCamera(glm::vec3 loc)
{
	cameraPos = loc;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4fv("view", glm::value_ptr(view));
}

void	Scop::rotateObject(float angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
	shader.setMat4fv("model", glm::value_ptr(model));
}

void	Scop::calcDeltaTime(void)
{
	float	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void	Scop::useShader(void)
{
	texLoaded ? Scop::shader.use(1) : Scop::shader.use(0);
}

Shader		Scop::shader;
bool		Scop::texLoaded;
glm::vec3	Scop::cameraPos = glm::vec3(0.0f, 0.0f,  0.0f);
glm::vec3	Scop::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3	Scop::cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3	Scop::cameraSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraUpSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraDownSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraRightSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraLeftSpeed = glm::vec3(0.0f);
