#include <Shader.hpp>

Shader::Shader(void)
{
}

Shader::~Shader(void)
{
}

void	Shader::read(const char *filepath)
{
	int					i;
	std::string			line;
	std::ifstream		file(filepath);
	std::stringstream	ss[2];

	if (!file.is_open())
	{
		std::cerr << "Failed to open file\n";
		return ;
	}
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

static void	compile(unsigned int shader, const char *shader_source)
{
	int		success;
	char	infoLog[512];

	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "shader compilation failed\n" << infoLog << std::endl;
		std::cerr << shader_source << std::endl;
	}
}

void	Shader::create(void)
{
	int				success;
	char			infoLog[512];
	const char		*vertexShaderSource = _vertex_shader.c_str();
	const char		*fragmentShaderSource = _fragment_shader.c_str();
	unsigned int	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned int	shaderProgram = glCreateProgram();

	compile(vertexShader, vertexShaderSource);
	compile(fragmentShader, fragmentShaderSource);
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Shader program linking failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	_id = shaderProgram;
}

void	Shader::use(void)
{
	glUseProgram(_id);
}
