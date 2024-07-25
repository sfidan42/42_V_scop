#include <main.h>

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

GLuint	CreateShader(ShaderProgramSource &source)
{
	GLuint	program;
	GLuint	vs;
	GLuint	fs;

	program = glCreateProgram();
	vs = CompileShader(GL_VERTEX_SHADER, source.vertexSource);
	fs = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
