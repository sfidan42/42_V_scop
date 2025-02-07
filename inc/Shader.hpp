#pragma once
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

class Shader
{
private:
	int			_success;
	char		_infoLog[512];
	std::string	_vertex_shader;
	std::string	_fragment_shader;
public:
	Shader(void);
	~Shader(void);
	void			parse(const char *filepath);
	unsigned int	create(void);
private:
	void	_compile(unsigned int shader, const char *shader_source);
};
