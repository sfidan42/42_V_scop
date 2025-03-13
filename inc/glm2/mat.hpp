#pragma once
# include <cmath>
# include "vec.hpp"
# define MAT	mat<N, T>

namespace glm2
{
	template <unsigned int N, typename T>
	class mat
	{
	private:
		glm2::VEC	_data[N];
	public:
		mat(void);
		mat(T num);
		mat(const MAT &mat);
		mat	&operator=(const MAT &mat);
		~mat(void);
	public:
		glm2::VEC		&operator[](int i);
		glm2::VEC const &operator[](int i) const;
	};

	typedef mat<2, float>	mat2;
	typedef mat<3, float>	mat3;
	typedef mat<4, float>	mat4;
}

#include "mat.inl"
