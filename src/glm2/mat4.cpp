#include <glm2/mat4.hpp>

namespace glm2
{
	mat4::mat4(float num)
	{
		for (int i = 0; i < 16; i++)
			_m[i] = num;
	}

	mat4::mat4(const mat4 &mat)
	{
		for (int i = 0; i < 16; i++)
			_m[i] = mat._m[i];
	}

	mat4	&mat4::operator=(const mat4 &mat)
	{
		if (this != &mat)
			*this = mat;
		return (*this);
	}

	mat4::~mat4(void)
	{
	}
}
