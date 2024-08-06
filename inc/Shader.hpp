#ifndef __SHADER__
# define __SHADER__
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	GLint		_location;
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
	void	changeColor(float r, float g, float b, float a);
};

# endif