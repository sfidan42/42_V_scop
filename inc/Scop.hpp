#ifndef SCOP_H
# define SCOP_H
# include "Shader.hpp"
# include "WavefrontObj.hpp"
# include <iostream>
# include <math.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class Scop
{
public:
	static Shader		shader;
	static glm::vec3	cameraSpeed;
private:
	glm::mat4	model;
	glm::mat4	view;
	glm::mat4	projection;
private:
	float	speedCoeff;
	float	deltaTime;
	float	lastFrame;
private:
	static bool			texLoaded;
	static glm::vec3	cameraPos;
	static glm::vec3	cameraFront;
	static glm::vec3	cameraUp;
	static glm::vec3	cameraUpSpeed;
	static glm::vec3	cameraDownSpeed;
	static glm::vec3	cameraRightSpeed;
	static glm::vec3	cameraLeftSpeed;
public:
	Scop();
	~Scop();
	static void	framebuffer_size_callback(GLFWwindow* window, int w, int h);
	static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void	loadTexture(const char *texPath);
	void	moveCamera(glm::vec3 dist);
	void	locateCamera(glm::vec3 loc);
	void	rotateObject(float angle, glm::vec3 axis);
	void	calcDeltaTime(void);
	void	setMVP(void);
	void	setLightPos(glm::vec3 lightPos);
	void	setMaterial(tMaterial mat);
	void	setSpeedCoeff(float speedCoeff);
	void	useShader(void); // automatic detection of the shader to use
};

#endif
