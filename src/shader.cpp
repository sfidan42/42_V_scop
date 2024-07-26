#include <scop.hpp>

/*
* Given a file path, this function will read the file and parse it to a string.
* The string will be split into two parts: vertex shader and fragment shader.
*/
void	Shader::Parse(void)
{
	std::ifstream		file(_filepath);
	std::string			line;
	std::stringstream	ss[2];
	enum class			ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType			type;

	type = ShaderType::NONE;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}
	_vertexSource = ss[0].str();
	_fragmentSource = ss[1].str();
}

static
GLuint	CompileShader(GLenum type, const std::string &source)
{
	GLuint		id;
	const char	*src;
	GLint		result;

	id = glCreateShader(type);
	src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint	length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char	*message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cerr << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

void	Shader::Create(void)
{
	GLuint	vs;
	GLuint	fs;

	_program = glCreateProgram();
	vs = CompileShader(GL_VERTEX_SHADER, _vertexSource);
	fs = CompileShader(GL_FRAGMENT_SHADER, _fragmentSource);
	glAttachShader(_program, vs);
	glAttachShader(_program, fs);
	glLinkProgram(_program);
	glValidateProgram(_program);
	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::Shader(void) : _program(0) {}

Shader::~Shader(void)
{
	glDeleteProgram(_program);
}

void	Shader::operator<<(const char *filepath)
{
	_filepath = filepath;
	Parse();
	Create();
}

void	Shader::use(void)
{
	GLCall(glUseProgram(_program));
	changeColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void	Shader::changeColor(float r, float g, float b, float a)
{
	GLint	location;

	GLCall(location = glGetUniformLocation(_program, "u_Color"));
	ASSERT(location != -1);
	GLCall(glUniform4f(location, r, g, b, a));
}
