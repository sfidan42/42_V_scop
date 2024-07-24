#ifndef MAIN_H
# define MAIN_H
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <iostream>
# include <string>

GLuint	CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
void	ParseShader(const std::string &filepath);

#endif