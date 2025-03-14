namespace glm2
{
	GLM2
	inline VEC::vec(void)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] = static_cast<T>(0);
	}

	GLM2
	inline VEC::vec(const VEC& other)
	{
		for (unsigned int i = 0; i < N; ++i)
			_data[i] = other._data[i];
	}

	GLM2
	inline VEC::~vec(void)
	{
	}

	GLM2
	inline VEC	&VEC::operator=(const VEC& other)
	{
		if (this != &other)
		{
			for (unsigned int i = 0; i < N; ++i)
				_data[i] = other._data[i];
		}
		return *this;
	}

	GLM2
	inline VEC	&VEC::operator=(const T *arr)
	{
		static_assert(sizeof(arr) == N, "Array size must match vector dimension");
		for (unsigned int i = 0; i < N; ++i)
			_data[i] = arr[i];
		return *this;
	}

	GLM2
	inline VEC::vec(T x)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] = x;
	}

	GLM2
	inline VEC::vec(T x, T y)
	{
		static_assert(N == 2, "vec(x, y) is only valid for vec2");
		_data[0] = x;
		_data[1] = y;
	}

	GLM2
	inline VEC::vec(T x, T y, T z)
	{
		static_assert(N == 3, "vec(x, y, z) is only valid for vec3");
		_data[0] = x;
		_data[1] = y;
		_data[2] = z;
	}

	GLM2
	inline VEC::vec(T x, T y, T z, T w)
	{
		static_assert(N == 4, "vec(x, y, z, w) is only valid for vec4");
		_data[0] = x;
		_data[1] = y;
		_data[2] = z;
		_data[3] = w;
	}

	GLM2
	inline T	&VEC::operator[](int i)
	{
		return _data[i];
	}

	GLM2
	inline T const	&VEC::operator[](int i) const
	{
		return _data[i];
	}

	GLM2
	inline VEC	&VEC::operator*=(T b)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] *= b;
		return *this;
	}

	GLM2
	inline VEC	&VEC::operator-=(const VEC& b)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] -= b[i];
		return *this;
	}

	GLM2
	inline VEC	&VEC::operator+=(const VEC& b)
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] += b[i];
		return *this;
	}

	GLM2
	inline VEC const	&VEC::operator*=(T b) const
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] *= b;
		return *this;
	}

	GLM2
	inline VEC const	&VEC::operator-=(const VEC& b) const
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] -= b[i];
		return *this;
	}

	GLM2
	inline VEC const	&VEC::operator+=(const VEC& b) const
	{
		for (unsigned int i = 0; i < N; i++)
			_data[i] += b[i];
		return *this;
	}

	GLM2
	inline VEC	operator+(const VEC &a, const VEC &b)
	{
		VEC	res;

		for (unsigned int i = 0; i < N; i++)
			res[i] = a[i] + b[i];
		return (res);
	}

	GLM2
	inline VEC	operator-(const VEC &a, const VEC &b)
	{
		VEC	res;

		for (unsigned int i = 0; i < N; i++)
			res[i] = a[i] - b[i];
		return (res);
	}

	GLM2
	inline VEC	operator*(const VEC &a, const VEC &b)
	{
		VEC	res;

		for (unsigned int i = 0; i < N; i++)
			res[i] = a[i] * b[i];
		return (res);
	}

	GLM2
	inline VEC	operator*(const VEC &a, T b)
	{
		VEC	res;

		for (unsigned int i = 0; i < N; i++)
			res[i] = a[i] * b;
		return (res);
	}

	GLM2
	bool	operator==(const VEC &a, const VEC &b)
	{
		for (unsigned int i = 0; i < N; i++)
			if (a[i] != b[i])
				return (false);
		return (true);
	}
}
