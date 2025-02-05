#include <Shader.hpp>

Shader::Shader(void)
{
}

Shader::~Shader(void)
{
}

void	Shader::parse(const char *filepath)
{
	std::ifstream		file(filepath);
	std::string			line;
	std::stringstream	ss[2];
	int					i;

	i = -1;
	while (getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				i = 0;
			else if (line.find("fragment") != std::string::npos)
				i = 1;
		}
		else if (i != -1)
			ss[i] << line << '\n';
	}
	_vertex_shader = ss[0].str();
	_fragment_shader = ss[1].str();
}

void	Shader::_compile(unsigned int shader, const char *shader_source)
{
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &_success);
	if (!_success)
	{
		glGetShaderInfoLog(shader, 512, NULL, _infoLog);
		std::cerr << "shader compilation failed\n" << _infoLog << std::endl;
	}
}

void	Shader::use(void)
{

	const char		*vertexShaderSource = _vertex_shader.c_str();
	const char		*fragmentShaderSource = _fragment_shader.c_str();
	
	unsigned int	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	_compile(vertexShader, vertexShaderSource);
	_compile(fragmentShader, fragmentShaderSource);

	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &_success);
	if (!_success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, _infoLog);
		std::cerr << "Shader program linking failed\n" << _infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
