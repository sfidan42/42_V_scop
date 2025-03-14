#include <Scop.hpp>

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
	cerr << "OpenGL error: (" << error << ")" << endl;
	return (false);
}
