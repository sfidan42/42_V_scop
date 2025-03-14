#pragma once
# include <vector>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

using namespace std;

typedef	struct
{
	string	vertex;
	string	fragment;
}				tShader;

class Shader
{
private:
	unsigned int			_program;
	vector<unsigned int>	_programs;
	vector<tShader>			_shaders;
public:
	Shader(void);
	~Shader(void);
public:
	void	config(const unsigned int count);
	void	read(const char *filepath);
	void	create(void);
	void	use(unsigned int index);
public:
	void	setMat4fv(const string &name, const float *value);
	void	set3f(const string &name, const float a, const float b, const float c);
};
