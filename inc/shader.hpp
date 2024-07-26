#ifndef SHADER_H
# define SHADER_H
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	GLuint		_program;
	std::string	_filepath;
	std::string	_vertexSource;
	std::string	_fragmentSource;
private:
	void	Parse(void);
	void	Create(void);
public:
	Shader(void);
	~Shader(void);
	void	operator<<(const char *filepath);
	void	use(void);
};

# endif