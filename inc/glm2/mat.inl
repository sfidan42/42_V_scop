namespace glm2
{
	GLM2
	inline MAT::mat(void)
	{
		T	num;
		
		num = static_cast<T>(0);
		for (unsigned int i = 0; i < N; i++)
			_data[i] = glm2::VEC(num);
	}

	GLM2
	inline MAT::mat(T num)
	{
		glm2::VEC	vec;
		T			zero;

		zero = static_cast<T>(0);
		for (unsigned int i = 0; i < N; i++)
		{
			vec = glm2::VEC(zero);
			vec[i] = num;
			_data[i] = vec;
		}
	}

	GLM2
	inline MAT::mat(const MAT &mat)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] = mat._data[i];
	}

	GLM2
	inline MAT &MAT::operator=(const MAT &mat)
	{
		if (this != &mat)
		{
			for (unsigned int i = 0; i < N; i++)
				_data[i] = mat._data[i];
		}
		return *this;
	}

	GLM2
	inline glm2::VEC	&MAT::operator[](int i)
	{
		return _data[i];
	}

	GLM2
	inline const glm2::VEC	&MAT::operator[](int i) const
	{
		return _data[i];
	}

	GLM2
	inline MAT::~mat(void)
	{
	}
}
