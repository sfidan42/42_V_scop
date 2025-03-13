#ifndef SCOP_H
# define SCOP_H
# include "Shader.hpp"
# include "WavefrontObj.hpp"
# include <iostream>
# include <math.h>
# include "glm2/vec.hpp"
# include "glm2/mat.hpp"
# include "glm2/transform.hpp"
# include <glm/gtc/matrix_transform.hpp>
# include <glm/glm.hpp>
# include <glm/gtc/type_ptr.hpp>

enum class Rotate
{
	NONE,
	PITCH_PLUS,
	PITCH_MINUS,
	YAW_PLUS,
	YAW_MINUS,
	ROLL_PLUS,
	ROLL_MINUS
};

class Scop
{
public:
	static Shader	shader;
private:
	glm2::mat4	model;
	glm::mat4	view;
	glm2::mat4	projection;
private:
	float	speedCoeff;
	float	deltaTime;
	float	lastFrame;
private:
	static Rotate	rotate;
	static bool		texLoaded;
	static bool		leftButtonPressed;
	static bool		firstMouse;
private:
	static float		yaw;
	static float		pitch;
	static double		lastX;
	static double		lastY;
	static glm::vec3	cameraPos;
	static glm::vec3	cameraFront;
	static glm::vec3	cameraUp;
	static glm::vec3	cameraSpeed;
	static glm::vec3	cameraUpSpeed;
	static glm::vec3	cameraDownSpeed;
	static glm::vec3	cameraRightSpeed;
	static glm::vec3	cameraLeftSpeed;
	static glm::vec3	cameraFrontSpeed;
	static glm::vec3	cameraBackwardSpeed;
public: // .
	Scop();
	~Scop();
	void	moveCamera();
	void	locateCamera(glm::vec3 loc);
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

#endif
