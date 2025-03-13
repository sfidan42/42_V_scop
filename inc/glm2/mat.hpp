#pragma once
# include "vec.hpp"

namespace glm2
{
	template <unsigned int N, typename T>
	class mat
	{
	private:
		glm::vec<N, T>	_data[N];
	public:
		mat(void);
		mat(float num);
		mat(const mat<N, T> &mat);
		mat	&operator=(const mat<N, T> &mat);
		~mat(void);
	public:
		glm::vec<N, T>			&operator[](int i);
		glm::vec<N, T> const 	&operator[](int i) const;
	};

	typedef mat<4, float>	mat4;
}

#include "mat.inl"
