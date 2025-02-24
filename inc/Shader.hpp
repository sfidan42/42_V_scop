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
	unsigned int	_id;
	std::string		_vertex_shader;
	std::string		_fragment_shader;
public:
	Shader(void);
	~Shader(void);
public:
	void	read(const char *filepath);
	void	create(void);
	void	use(void);
public:
	void	setMat4fv(const std::string &name, const float *value);
	void	set3f(const std::string &name, const float a, const float b, const float c);
};
