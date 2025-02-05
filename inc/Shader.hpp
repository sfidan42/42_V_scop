#pragma once
# include <string>
# include <fstream>
# include <sstream>
# include "scop.hpp"

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
	void	parse(const char *filepath);
	void	use(void);
private:
	void	_compile(unsigned int shader, const char *shader_source);
};
