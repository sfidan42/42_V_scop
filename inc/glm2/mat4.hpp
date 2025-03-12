#pragma once

namespace glm2
{
	class mat4
	{
	private:
		float	_m[16];
		mat4(void);
	public:
		mat4(float num);
		mat4(const mat4 &mat);
		mat4	&operator=(const mat4 &mat);
		~mat4(void);
	};
}
