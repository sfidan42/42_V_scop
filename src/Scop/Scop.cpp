#include <Scop.hpp>

Scop::Scop(void)
{
	model = glm2::mat4(1.0f);
	view = glm2::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm2::perspective(glm2::radians(70.0f), 800.0f / 600.0f, 0.1f, 20000.0f);
	speedCoeff = 0.0f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

Scop::~Scop(void) { }

void	Scop::moveCamera(void)
{
	if (speedCoeff == 0.0f)
		std::cout << "Speed coefficient not set" << std::endl;
	cameraPos += cameraSpeed * speedCoeff * deltaTime;
	view = glm2::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4fv("view", glm2::value_ptr(view));
}

void	Scop::locateCamera(glm2::vec3 loc)
{
	cameraPos = loc;
	view = glm2::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4fv("view", glm2::value_ptr(view));
}

void	Scop::transformObject(void)
{
	float		angle;
	glm2::vec3	axis;

	switch (rotate)
	{
		case Rotate::PITCH_PLUS: angle = 1.0f; axis = glm2::vec3(1.0f, 0.0f, 0.0f); break;
		case Rotate::PITCH_MINUS: angle = -1.0f; axis = glm2::vec3(1.0f, 0.0f, 0.0f); break;
		case Rotate::YAW_PLUS: angle = 1.0f; axis = glm2::vec3(0.0f, 1.0f, 0.0f); break;
		case Rotate::YAW_MINUS: angle = -1.0f; axis = glm2::vec3(0.0f, 1.0f, 0.0f); break;
		case Rotate::ROLL_PLUS: angle = 1.0f; axis = glm2::vec3(0.0f, 0.0f, 1.0f); break;
		case Rotate::ROLL_MINUS: angle = -1.0f; axis = glm2::vec3(0.0f, 0.0f, 1.0f); break;
		default: angle = M_PI / 10.0f; axis = glm2::vec3(0.0f, 1.0f, 0.0f); break;
	}
	model = glm2::rotate(model, glm2::radians(angle), axis);
	shader.setMat4fv("model", glm2::value_ptr(model));
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

Shader	Scop::shader;

Rotate	Scop::rotate = Rotate::NONE;
bool	Scop::texLoaded = false;
bool	Scop::leftButtonPressed = false;
bool	Scop::firstMouse = true;

float		Scop::yaw = -90.0f;
float		Scop::pitch = 0.0f;
double		Scop::lastX;
double		Scop::lastY;
glm2::vec3	Scop::cameraPos = glm2::vec3(0.0f, 0.0f,  0.0f);
glm2::vec3	Scop::cameraFront = glm2::vec3(0.0f, 0.0f, -1.0f);
glm2::vec3	Scop::cameraUp = glm2::vec3(0.0f, 1.0f,  0.0f);
glm2::vec3	Scop::cameraSpeed = glm2::vec3(0.0f);
glm2::vec3	Scop::cameraUpSpeed = glm2::vec3(0.0f);
glm2::vec3	Scop::cameraDownSpeed = glm2::vec3(0.0f);
glm2::vec3	Scop::cameraRightSpeed = glm2::vec3(0.0f);
glm2::vec3	Scop::cameraLeftSpeed = glm2::vec3(0.0f);
glm2::vec3	Scop::cameraFrontSpeed = glm2::vec3(0.0f);
glm2::vec3	Scop::cameraBackwardSpeed = glm2::vec3(0.0f);
