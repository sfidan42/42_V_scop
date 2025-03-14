#pragma once
# include "mat.hpp"

// 1 / sqrt(x)
inline float	Q_rsqrt(float y)
{
	long i;
	float x2;
	const float threehalfs = 1.5F;

	x2 = y * 0.5F;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

namespace glm2
{
	template <unsigned int N, typename T>
	inline T	dot(glm2::vec<N, T> const &a, glm2::vec<N, T> const &b)
	{
		T	res;

		res = T(0);
		for (unsigned int i = 0; i < N; i++)
			res += a[i] * b[i];
		return (res);
	}

	template <typename T>
	inline T	length(const glm2::vec<3, T> &v)
	{
		return static_cast<T>(sqrt(dot(v, v)));
	}

	template <typename T>
	inline glm2::vec<3, T>	cross(glm2::vec<3, T> const &v1, glm2::vec<3, T> const &v2)
	{
		return (glm2::vec<3, T>(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		));
	}

	template <unsigned int N, typename T>
	inline glm2::vec<N, T>	normalize(glm2::vec<N, T> const &v)
	{
		return (v * (T(1) / length(v)));
	}

	template <typename T>
	inline glm2::mat<4, T>	lookAt(glm2::vec<3, T> const &eye, glm2::vec<3, T> const &center, glm2::vec<3, T> const &up)
	{
		glm2::vec<3, T>	f(glm2::normalize(center - eye));
		glm2::vec<3, T>	s(glm2::normalize(glm2::cross(f, up)));
		glm2::vec<3, T>	u(glm2::cross(s, f));
		glm2::mat<4, T>	Result(1);

		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] =-f.x;
		Result[1][2] =-f.y;
		Result[2][2] =-f.z;
		Result[3][0] =-dot(s, eye);
		Result[3][1] =-dot(u, eye);
		Result[3][2] = dot(f, eye);

		return (Result);
	}

	template <typename T>
	inline glm2::mat<4, T>	rotate(glm2::mat<4, T> const &mat, T angle, glm2::vec<3, T> const &axis)
	{
		glm2::mat<4, T>	ret = mat;
		T				c = cos(angle);
		T				s = sin(angle);
		glm2::vec<3, T>	a = glm2::normalize(axis);
		glm2::vec<3, T>	temp = a * (1 - c);
		glm2::mat3		rot;

		rot[0] = glm2::vec<3, T>(c + temp.x * a.x, temp.x * a.y + s * a.z, temp.x * a.z - s * a.y);
		rot[1] = glm2::vec<3, T>(temp.y * a.x - s * a.z, c + temp.y * a.y, temp.y * a.z + s * a.x);
		rot[2] = glm2::vec<3, T>(temp.z * a.x + s * a.y, temp.z * a.y - s * a.x, c + temp.z * a.z);

		ret[0] = mat[0] * rot[0][0] + mat[1] * rot[0][1] + mat[2] * rot[0][2];
		ret[1] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
		ret[2] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
		return (ret);
	}

	template <typename T>
	inline glm2::mat<4, T>	perspective(T fovy, T aspect, T near, T far)
	{
		glm2::mat<4, T>	ret = glm2::mat<4, T>(0.0f);
		T			tanHalfFovy = tan(fovy / T(2));

		ret[0][0] = T(1) / (aspect * tanHalfFovy);
		ret[1][1] = T(1) / (tanHalfFovy);
		ret[2][2] = -(far + near) / (far - near);
		ret[2][3] = -T(1);
		ret[3][2] = -(T(2) * far * near) / (far - near);
		return (ret);
	}

	inline float	radians(float degree)
	{
		return (M_PI * (degree / 180.0));
	}

	template <unsigned int N, typename T>
	inline const float	*value_ptr(const glm2::mat<N, T> &m)
	{
		return &(m[0].x);
	}
}
