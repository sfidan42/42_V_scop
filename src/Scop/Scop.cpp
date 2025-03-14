#include <Scop.hpp>

Scop::Scop(void)
{
	model = mat4(1.0f);
	view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = perspective(radians(70.0f), 800.0f / 600.0f, 0.1f, 20000.0f);
	speedCoeff = 0.0f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

Scop::~Scop(void) { }

void	Scop::moveCamera(void)
{
	if (speedCoeff == 0.0f)
		cout << "Speed coefficient not set" << endl;
	cameraPos += cameraSpeed * speedCoeff * deltaTime;
	view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4fv("view", value_ptr(view));
}

void	Scop::locateCamera(vec3 loc)
{
	cameraPos = loc;
	view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.setMat4fv("view", value_ptr(view));
}

void	Scop::transformObject(void)
{
	float	angle;
	vec3	axis;

	switch (Scop::rotation)
	{
		case Rotation::PITCH_PLUS:	angle = -2.0f;	axis = vec3(1.0f, 0.0f, 0.0f); break;
		case Rotation::PITCH_MINUS:	angle =  2.0f;	axis = vec3(1.0f, 0.0f, 0.0f); break;
		case Rotation::YAW_PLUS:	angle =  2.0f;	axis = vec3(0.0f, 1.0f, 0.0f); break;
		case Rotation::YAW_MINUS:	angle = -2.0f;	axis = vec3(0.0f, 1.0f, 0.0f); break;
		case Rotation::ROLL_PLUS:	angle =  2.0f;	axis = vec3(0.0f, 0.0f, 1.0f); break;
		case Rotation::ROLL_MINUS:	angle = -2.0f;	axis = vec3(0.0f, 0.0f, 1.0f); break;
		default: 					angle =  0.7f;	axis = vec3(0.0f, 1.0f, 0.0f); break;
	}
	model = rotate(model, radians(angle), axis);
	shader.setMat4fv("model", value_ptr(model));
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

bool		Scop::texLoaded			= false;
bool		Scop::leftButtonPressed	= false;
bool		Scop::firstMouse		= true;

Rotation	Scop::rotation			= Rotation::NONE;

float		Scop::yaw				= -90.0f;
float		Scop::pitch				=   0.0f;
double		Scop::lastX;
double		Scop::lastY;
vec3		Scop::cameraPos			= vec3(0.0f, 0.0f, 0.0f);
vec3		Scop::cameraFront		= vec3(0.0f, 0.0f, -1.0f);
vec3		Scop::cameraUp			= vec3(0.0f, 1.0f, 0.0f);
vec3		Scop::cameraSpeed		= vec3(0.0f);
vec3		Scop::cameraSpeeds[6]	= { 0.0f };
