#pragma once
# include <glm/glm.hpp>

// 1 / sqrt(x)
inline float	Q_rsqrt( float y )
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
	template <typename T>
	inline T	dot(glm::vec<3, T> const &a, glm::vec<3, T> const &b)
	{
		glm::vec<3, T>	tmp(a * b);

		return (tmp.x + tmp.y + tmp.z);
	}

	template <typename T>
	inline T	length(const glm::vec<3, T> &v)
	{
		return static_cast<T>(sqrt(dot(v, v)));
	}

	template <typename T>
	inline glm::vec<3, T>	cross(glm::vec<3, T> const &v1, glm::vec<3, T> const &v2)
	{
		return (glm::vec<3, T>(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		));
	}

	template <typename T>
	inline glm::vec<3, T>	normalize(glm::vec<3, T> const &v)
	{
		return (v * Q_rsqrt(glm2::dot(v, v)));
	}

	template <typename T>
	inline glm::mat4	lookAt(glm::vec<3, T> const &camPos, glm::vec<3, T> const &camTarget, glm::vec<3, T> const &camUp)
	{
		glm::vec<3, T>	f = glm2::normalize(camTarget - camPos);
		glm::vec<3, T>	u = glm2::normalize(camUp);
		glm::vec<3, T>	s = glm2::normalize(glm2::cross(f, u));

		glm::mat4	ret = glm::mat4(1.0f);
		ret[0][0] = s.x;
		ret[1][0] = s.y;
		ret[2][0] = s.z;
		ret[0][1] = u.x;
		ret[1][1] = u.y;
		ret[2][1] = u.z;
		ret[0][2] = -f.x;
		ret[1][2] = -f.y;
		ret[2][2] = -f.z;
		ret[3][0] = -glm2::dot(s, camPos);
		ret[3][1] = -glm2::dot(u, camPos);
		ret[3][2] = glm2::dot(f, camPos);
		return (ret);
	}

	template <typename T>
	inline glm::mat4	rotate(glm::mat4 const &mat, T angle, glm::vec3 const &axis)
	{
		glm::mat4	ret = mat;
		T			c = cos(angle);
		T			s = sin(angle);
		glm::vec3	a = glm2::normalize(axis);
		glm::vec3	temp = (1 - c) * a;

		glm::mat3	rot = glm::mat3(
			c + temp.x * a.x, temp.x * a.y + s * a.z, temp.x * a.z - s * a.y,
			temp.y * a.x - s * a.z, c + temp.y * a.y, temp.y * a.z + s * a.x,
			temp.z * a.x + s * a.y, temp.z * a.y - s * a.x, c + temp.z * a.z
		);

		ret[0] = mat[0] * rot[0][0] + mat[1] * rot[0][1] + mat[2] * rot[0][2];
		ret[1] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
		ret[2] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
		return (ret);
	}

	template <typename T>
	inline glm::mat4	perspective(T fovy, T aspect, T near, T far)
	{
		glm::mat4	ret = glm::mat4(0.0f);
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

	inline const float	*value_ptr(glm::mat4 &mat)
	{
		return &(mat[0].x);
	}
}
