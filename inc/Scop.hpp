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
	static Shader	shader;
public:
	static bool		texLoaded;

	static float		deltaTime;
	static float		lastFrame;

	static float		speedCoeff;
	static glm::vec3	cameraSpeed;
private:
	static glm::vec3	cameraPos;
	static glm::vec3	cameraFront;
	static glm::vec3	cameraUp;
	glm::mat4			model;
	glm::mat4			view;
	glm::mat4			projection;
	static glm::vec3	cameraUpSpeed;
	static glm::vec3	cameraDownSpeed;
	static glm::vec3	cameraRightSpeed;
	static glm::vec3	cameraLeftSpeed;
public:
	Scop();
	~Scop();
	static void	framebuffer_size_callback(GLFWwindow* window, int w, int h);
	static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void	loadTexture(const char *texPath);
	void	moveCamera(glm::vec3 dist) { cameraPos += dist; view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); shader.setMat4fv("view", glm::value_ptr(view)); }
	void	rotateObject(float angle, glm::vec3 axis) { model = glm::rotate(model, glm::radians(angle), axis); shader.setMat4fv("model", glm::value_ptr(model)); }
	glm::vec3	getCameraPos() { return cameraPos; }
	glm::vec3	getCameraFront() { return cameraFront; }
	glm::vec3	getCameraUp() { return cameraUp; }
	glm::mat4	getModel() { return model; }
	glm::mat4	getView() { return view; }
	glm::mat4	getProjection() { return projection; }
	
};

#endif
