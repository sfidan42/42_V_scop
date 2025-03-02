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

Scop::~Scop(void) { }

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

void	Scop::rotateObject(void)
{
	float		angle;
	glm::vec3	axis;
	switch (arrow)
	{
		case Arrow::UP: angle = -2.0f; axis = glm::vec3(1.0f, 0.0f, 0.0f); break;
		case Arrow::LEFT: angle = -2.0f; axis = glm::vec3(0.0f, 1.0f, 0.0f); break;
		case Arrow::DOWN: angle = 2.0f; axis = glm::vec3(1.0f, 0.0f, 0.0f); break;
		case Arrow::RIGHT: angle = 2.0f; axis = glm::vec3(0.0f, 1.0f, 0.0f); break;
		default: angle = M_PI / 10.0f; axis = glm::vec3(0.0f, 1.0f, 0.0f); break;
	}
	model = glm::rotate(model, glm::radians(angle), axis);
	shader.setMat4fv("model", glm::value_ptr(model));
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

Arrow		Scop::arrow = Arrow::NONE;
bool		Scop::texLoaded = false;
bool		Scop::leftButtonPressed = false;
bool		Scop::firstMouse = true;

float		Scop::yaw = -90.0f;
float		Scop::pitch = 0.0f;
double		Scop::lastX;
double		Scop::lastY;
glm::vec3	Scop::cameraPos = glm::vec3(0.0f, 0.0f,  0.0f);
glm::vec3	Scop::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3	Scop::cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3	Scop::cameraSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraUpSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraDownSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraRightSpeed = glm::vec3(0.0f);
glm::vec3	Scop::cameraLeftSpeed = glm::vec3(0.0f);
