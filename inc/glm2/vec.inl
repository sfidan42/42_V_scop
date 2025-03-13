namespace glm2
{
	template <unsigned int N, typename T>
	vec<N, T>::vec(void)
	{
		for (unsigned int i = 0; i < N; ++i)
			_data[i] = 0;
	}

	template <unsigned int N, typename T>
	vec<N, T>::vec(const vec<N, T> &vec)
	{
		for (unsigned int i = 0; i < N; ++i)
			_data[i] = vec[i];
	}

	template <unsigned int N, typename T>
	vec<N, T>	&vec<N, T>::operator=(const vec<N, T> &vec)
	{
		if (this != &vec)
			for (unsigned int i = 0; i < N; ++i)
				this->_data[i] = vec[i];
		return *this;
	}

	template <unsigned int N, typename T>
	vec<N, T>::~vec(void)
	{
	}

	template <unsigned int N, typename T>
	template <typename... Args>
	vec<N, T>::vec(Args... args)
	{
		static_assert(sizeof...(Args) == N, "Number of arguments must match vector dimension");
		std::array<T, N> tempArray = {static_cast<T>(args)...};
		_data = tempArray;
	}

	template <unsigned int N, typename T>
	template <typename... Args>
	vec<N, T>	&vec<N, T>::operator=(Args... args)
	{
		static_assert(sizeof...(Args) == N, "Number of arguments must match vector dimension");
		std::array<T, N> tempArray = {static_cast<T>(args)...};
		_data = tempArray;
		return *this;
	}
};
