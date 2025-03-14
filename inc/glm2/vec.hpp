#pragma once
# define GLM2_VEC_ITER(X)	for (unsigned int i = 0; i < N; i++) { X }
# define GLM2_VEC			template <unsigned int N, typename T>
# define VEC				vec<N, T>

namespace glm2
{
	GLM2_VEC
	class vec
	{
	public:
		union
		{
			T		_data[N];
			struct	{ T	x, y, z; };
			struct	{ T	r, g, b; };
		};
	public:
		vec(void);
		vec(const VEC& vec);
		vec(T x);
		vec(T x, T y);
		vec(T x, T y, T z);
		vec(T x, T y, T z, T w);
		VEC	&operator=(T b);
		VEC	&operator=(const VEC& vec);
		VEC	&operator=(const T *arr);
		~vec(void);
	public:
		T	&operator[](unsigned int i);
		vec	&operator*=(T b);
		vec	&operator-=(const VEC& b);
		vec	&operator+=(const VEC& b);
	public:
		T const		&operator[](unsigned int i) const;
		vec	const	&operator*=(T b) const;
		vec	const	&operator-=(const VEC& b) const;
		vec	const	&operator+=(const VEC& b) const;
	};

	GLM2_VEC VEC	operator+(const VEC &a, const VEC &b);
	GLM2_VEC VEC	operator-(const VEC &a, const VEC &b);
	GLM2_VEC VEC	operator*(const VEC &a, const VEC &b);
	GLM2_VEC VEC	operator*(const VEC &a, T b);
	GLM2_VEC bool	operator==(const VEC &a, const VEC &b);

	typedef vec<2, float> vec2;
	typedef vec<3, float> vec3;
	typedef vec<4, float> vec4;
}

#include "vec.inl"
