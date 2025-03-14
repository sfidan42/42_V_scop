#pragma once
# include <array>

# define GLM2	template <unsigned int N, typename T>
# define VEC	vec<N, T>

namespace glm2
{
	GLM2
	class vec
	{
	public:
		union
		{
			std::array<T, N>	_data;
			struct
			{
				T	x;
				T	y;
				T	z;
				T	w;
			};
			struct
			{
				T	r;
				T	g;
				T	b;
				T	a;
			};
		};
	public:
		vec(void);
		vec(T t);
		vec(const VEC& vec);
		VEC	&operator=(const VEC& vec);
		VEC	&operator=(const T *arr);
		~vec(void);
	public:
		template <typename... Args>
		vec(Args... args);
	public:
		T			&operator[](int i);
		vec			&operator*=(T b);
		vec			&operator-=(const VEC& b);
		vec			&operator+=(const VEC& b);
	public:
		T const		&operator[](int i) const;
		vec	const	&operator*=(T b) const;
		vec	const	&operator-=(const VEC& b) const;
		vec	const	&operator+=(const VEC& b) const;
	};

	GLM2 VEC	operator+(const VEC &a, const VEC &b);
	GLM2 VEC	operator-(const VEC &a, const VEC &b);
	GLM2 VEC	operator*(const VEC &a, const VEC &b);
	GLM2 VEC	operator*(const VEC &a, T b);
	GLM2 bool	operator==(const VEC &a, const VEC &b);

	typedef vec<2, float> vec2;
	typedef vec<3, float> vec3;
	typedef vec<4, float> vec4;
}

#include "vec.inl"
