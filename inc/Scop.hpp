#ifndef SCOP_H
# define SCOP_H
# include "Shader.hpp"
# include "WavefrontObj.hpp"
# include "texture.h"
# include <iostream>
# include <math.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class Scop
{
public:
	static float	vRotate;
	static float	hRotate;
	static Shader	shader;
	static bool	texLoaded;
	static glm::vec3	cameraPos;
	static glm::vec3	cameraFront;
	static glm::vec3	cameraUp;
	static float	deltaTime;
	static float	lastFrame;
	static glm::vec3	cameraSpeed;
	static glm::vec3	cameraUpSpeed;
	static glm::vec3	cameraDownSpeed;
	static glm::vec3	cameraRightSpeed;
	static glm::vec3	cameraLeftSpeed;
	static float		speedCoeff;
public:
	Scop();
	~Scop();
	static void	framebuffer_size_callback(GLFWwindow* window, int w, int h);
	static void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
