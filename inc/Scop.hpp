#ifndef SCOP_H
# define SCOP_H
# include "Shader.hpp"
# include "Obj.hpp"
# include <iostream>
# include <math.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

void	transform(unsigned int shaderProgram, unsigned int i, glm::vec3 cubePositions[10], float angle_ratio);
void	processInput(GLFWwindow *window, unsigned int shaderProgram);
void	framebuffer_size_callback(GLFWwindow* window, int width, int height);
void	mouse_callback(GLFWwindow* window, double xpos, double ypos);

extern float   deltaTime; // Time between current frame and last frame
extern float   lastFrame; // Time of last frame

#endif
