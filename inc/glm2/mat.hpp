#pragma once
# include <cmath>
# include "vec.hpp"
# define GLM2_MAT_ITER(X)	for (unsigned int i = 0; i < M; i++) { X }
# define GLM2_MAT			template <unsigned int M, unsigned int N, typename T>
# define MAT				mat<M, N, T>

namespace glm2
{
	GLM2_MAT
	class mat
	{
	private:
		VEC	_data[M];
	public:
		mat(void);
		mat(T num);
		mat(const MAT &mat);
		mat	&operator=(const MAT &mat);
		~mat(void);
	public:
		VEC		&operator[](unsigned int i);
		VEC const &operator[](unsigned int i) const;
	};

	typedef mat<2, 2, float>	mat2;
	typedef mat<3, 3, float>	mat3;
	typedef mat<4, 4, float>	mat4;
}

#include "mat.inl"
