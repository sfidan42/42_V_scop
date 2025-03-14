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
	GLM2_VEC
	inline T	dot(VEC const &a, VEC const &b)
	{
		T	res;

		res = T(0);
		for (unsigned int i = 0; i < N; i++)
			res += a[i] * b[i];
		return (res);
	}

	GLM2_VEC
	inline T	length(const VEC &v)
	{
		return (T(sqrt(dot(v, v))));
	}

	inline vec3	cross(vec3 const &v1, vec3 const &v2)
	{
		return (vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		));
	}

	inline vec3	normalize(vec3 const &v)
	{
		return (v * Q_rsqrt(dot(v, v)));
	}

	inline mat4	lookAt(vec3 const &eye, vec3 const &center, vec3 const &up)
	{
		vec3	f(normalize(center - eye));
		vec3	s(normalize(cross(f, up)));
		vec3	u(cross(s, f));
		mat4	res(1.0f);

		res[0][0] = s.x;
		res[1][0] = s.y;
		res[2][0] = s.z;
		res[0][1] = u.x;
		res[1][1] = u.y;
		res[2][1] = u.z;
		res[0][2] =-f.x;
		res[1][2] =-f.y;
		res[2][2] =-f.z;
		res[3][0] =-dot(s, eye);
		res[3][1] =-dot(u, eye);
		res[3][2] = dot(f, eye);
		return (res);
	}

	inline mat4	rotate(mat4 const &mat, float angle, vec3 const &axis)
	{
		mat4	ret = mat;
		float	c = cos(angle);
		float	s = sin(angle);
		vec3	a = normalize(axis);
		vec3	temp = a * (1 - c);
		mat3	rot;

		rot[0] = vec3(c + temp.x * a.x, temp.x * a.y + s * a.z, temp.x * a.z - s * a.y);
		rot[1] = vec3(temp.y * a.x - s * a.z, c + temp.y * a.y, temp.y * a.z + s * a.x);
		rot[2] = vec3(temp.z * a.x + s * a.y, temp.z * a.y - s * a.x, c + temp.z * a.z);

		ret[0] = mat[0] * rot[0][0] + mat[1] * rot[0][1] + mat[2] * rot[0][2];
		ret[1] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
		ret[2] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
		return (ret);
	}

	inline mat4	perspective(float fovy, float aspect, float near, float far)
	{
		mat4	ret = mat4(0.0f);
		float	tanHalfFovy = tan(fovy / 2.0f);

		ret[0][0] = 1.0f / (aspect * tanHalfFovy);
		ret[1][1] = 1.0f / (tanHalfFovy);
		ret[2][2] = -(far + near) / (far - near);
		ret[2][3] = -1.0f;
		ret[3][2] = -(2.0f * far * near) / (far - near);
		return (ret);
	}

	inline float	radians(float degree)
	{
		return (M_PI * (degree / 180.0));
	}

	GLM2_MAT
	inline const T	*value_ptr(const MAT &m)
	{
		return &(m[0][0]);
	}
}
