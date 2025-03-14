#include "Shader.hpp"

void	Shader::setMat4fv(const string &name, const float *value)
{
    unsigned int loc = glGetUniformLocation(_program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, value);
}

void	Shader::set3f(const string &name, const float a, const float b, const float c)
{
    unsigned int loc = glGetUniformLocation(_program, name.c_str());
    glUniform3f(loc, a, b, c);
}
