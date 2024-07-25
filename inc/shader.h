#ifndef SHADER_H
# define SHADER_H
#include <fstream>
#include <sstream>

typedef struct s_ShaderProgramSource
{
	std::string	vertexSource;
	std::string	fragmentSource;
}				ShaderProgramSource;

unsigned int		CreateShader(ShaderProgramSource &source);
ShaderProgramSource	ParseShader(const std::string &filepath);

# endif