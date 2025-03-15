#pragma once
# include "Shader.hpp"
# include "WavefrontObj.hpp"
# include <iostream>
# include <math.h>
# include "glm2/vec.hpp"
# include "glm2/mat.hpp"
# include "glm2/transform.hpp"

using namespace glm2;
using namespace std;

enum eCameraSpeed
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Scop
{
public:
	static Shader	shader;
private:
	mat4	model;
	mat4	view;
	mat4	projection;
private:
	float	speedCoeff;
	float	deltaTime;
	float	lastFrame;
private:
	static bool	texLoaded;
	static bool	leftButtonPressed;
	static bool	firstMouse;
private:
	static float	rotationDegree;
	static vec3		rotationAxis;
private:
	static float	yaw;
	static float	pitch;
	static float	lastX;
	static float	lastY;
	static vec3	cameraPos;
	static vec3	cameraFront;
	static vec3	cameraUp;
	static vec3	cameraSpeed;
	static vec3	cameraSpeeds[6];
public: // .
	Scop();
	~Scop();
	void	moveCamera();
	void	locateCamera(vec3 loc);
	void	transformObject(void);
	void	calcDeltaTime(void);
	void	useShader(void); // automatic detection of the shader to use
public: // .callback
	static void	framebuffer_size_callback(GLFWwindow* window, int w, int h);
	static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void	mouse_callback(GLFWwindow* window, double xpos, double ypos);
public: // .load
	void	loadTexture(const char *texPath);
public: // .set
	void	setMVP(void);
	void	setLightPos(vec3 lightPos);
	void	setMaterial(tMaterial mat);
	void	setSpeedCoeff(float speedCoeff);
};

