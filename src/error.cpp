#include <scop.hpp>

void	GLClearError(void)
{
	while (glGetError() != GL_NO_ERROR);
}

bool	GLLogCall(void)
{
	GLenum	error;

	error = glGetError();
	if (error == GL_NO_ERROR)
		return (true);
	std::cerr << "OpenGL error: (" << error << ")" << std::endl;
	return (false);
}
