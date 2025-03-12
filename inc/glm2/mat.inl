namespace glm2
{
	template <unsigned int N, typename T>
	inline mat<N, T>::mat(void)
	{
		T	num;
		
		num = static_cast<T>(0);
		for (unsigned int i = 0; i < N; i++)
			_data[i] = glm::vec<N, T>(num);
	}

	template <unsigned int N, typename T>
	inline mat<N, T>::mat(float num)
	{
		glm::vec<N, T>	vec;

		for (unsigned int i = 0; i < N; i++)
		{
			vec = glm::vec<N, T>(0);
			vec[i] = num;
			_data[i] = vec;
		}
	}

	template <unsigned int N, typename T>
	inline mat<N, T>::mat(const mat<N, T> &mat)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] = mat._data[i];
	}

	template <unsigned int N, typename T>
	inline mat<N, T> &mat<N, T>::operator=(const mat<N, T> &mat)
	{
		if (this != &mat)
		{
			for (unsigned int i = 0; i < N; i++)
				_data[i] = mat._data[i];
		}
		return *this;
	}

	template <unsigned int N, typename T>
	inline glm::vec<N, T>	&mat<N, T>::operator[](int i)
	{
		return _data[i];
	}

	template <unsigned int N, typename T>
	inline const glm::vec<N, T>	&mat<N, T>::operator[](int i) const
	{
		return _data[i];
	}

	template <unsigned int N, typename T>
	inline mat<N, T>::~mat(void)
	{
	}
}
