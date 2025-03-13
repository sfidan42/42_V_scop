#pragma once
# include <array>
# include <glm/glm.hpp>

namespace glm2
{
	template <unsigned int N, typename T>
	class vec
	{
	private:
		std::array<T, N>	_data;
	public:
		vec(void);
		vec(const vec<N, T> &vec);
		vec<N, T>	&operator=(const vec<N, T> &vec);
		~vec(void);
	public:
		template <typename... Args>
		vec(Args... args);
		template <typename... Args>
		vec<N, T>	&operator=(Args... args);
	public:
		T		&operator[](int i);
		T const &operator[](int i) const;
	};

	typedef vec<3, float>	vec3;
}

#include "vec.inl"
