#pragma once
# include "Shader.hpp"
# include "WavefrontObj.hpp"
# include <iostream>
# include <math.h>
# include "glm2/vec.hpp"
# include "glm2/mat.hpp"
# include "glm2/transform.hpp"

enum class Rotation
{
	NONE,
	PITCH_PLUS,
	PITCH_MINUS,
	YAW_PLUS,
	YAW_MINUS,
	ROLL_PLUS,
	ROLL_MINUS
};

enum Direction
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
	FRONT,
	BACKWARD
};

class Scop
{
public:
	static Shader	shader;
private:
	glm2::mat4	model;
	glm2::mat4	view;
	glm2::mat4	projection;
private:
	float	speedCoeff;
	float	deltaTime;
	float	lastFrame;
private:
	static bool	texLoaded;
	static bool	leftButtonPressed;
	static bool	firstMouse;
private:
	static Rotation	rotation;
private:
	static float		yaw;
	static float		pitch;
	static double		lastX;
	static double		lastY;
	static glm2::vec3	cameraPos;
	static glm2::vec3	cameraFront;
	static glm2::vec3	cameraUp;
	static glm2::vec3	cameraSpeed;
	static glm2::vec3	cameraSpeeds[6];
public: // .
	Scop();
	~Scop();
	void	moveCamera();
	void	locateCamera(glm2::vec3 loc);
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
	void	setLightPos(glm2::vec3 lightPos);
	void	setMaterial(tMaterial mat);
	void	setSpeedCoeff(float speedCoeff);
};

