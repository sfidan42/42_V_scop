#pragma once

# include <vector>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

typedef	struct
{
	std::string	vertex;
	std::string	fragment;
}				tShader;

class Shader
{
private:
	unsigned int				_program;
	std::vector<unsigned int>	_programs;
	std::vector<tShader>		_shaders;
public:
	Shader(void);
	~Shader(void);
public:
	void	read(const char *filepath);
	void	create(void);
	void	use(unsigned int index);
public:
	void	setMat4fv(const std::string &name, const float *value);
	void	set3f(const std::string &name, const float a, const float b, const float c);
};
