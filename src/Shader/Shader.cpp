#include <Shader.hpp>

Shader::Shader()
{
}

Shader::~Shader(void)
{
}

void	Shader::config(const unsigned int count)
{
	_programs.reserve(count);
	_shaders.reserve(count);
}

void	Shader::read(const char *filepath)
{
	int				i;
	string			line;
	ifstream		file(filepath);
	stringstream	ss[2];

	if (!file.is_open())
	{
		cerr << "Failed to open file\n";
		return ;
	}
	if (_shaders.size() >= _shaders.capacity())
	{
		cerr << "Shader count exceeded\n";
		return ;
	}
	i = -1;
	while (getline(file, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
				i = 0;
			else if (line.find("fragment") != string::npos)
				i = 1;
		}
		else if (i != -1)
			ss[i] << line << '\n';
	}
	_shaders.push_back({ss[0].str(), ss[1].str()});
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
		cerr << "shader compilation failed\n" << infoLog << endl;
		cerr << shader_source << endl;
	}
}

void	Shader::create(void)
{
	int		success;
	char	infoLog[512];

	for (unsigned int i = 0; i < _shaders.size(); i++)
	{
		const char		*vertexShaderSource = _shaders[i].vertex.c_str();
		const char		*fragmentShaderSource = _shaders[i].fragment.c_str();
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
			cerr << "Shader program linking failed\n" << infoLog << endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		_programs.push_back(shaderProgram);
	}
}

void	Shader::use(unsigned int index)
{
	if (index >= _programs.size())
	{
		cerr << "Invalid program index: " << index << endl;
		return ;
	}
	_program = _programs[index];
	glUseProgram(_program);
}
