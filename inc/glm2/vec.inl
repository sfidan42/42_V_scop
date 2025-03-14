namespace glm2
{
	GLM2_VEC
	inline VEC::vec(void)
	{
		GLM2_VEC_ITER(_data[i] = static_cast<T>(0);)
	}

	GLM2_VEC
	inline VEC::vec(const VEC& other)
	{
		GLM2_VEC_ITER(_data[i] = other._data[i];)
	}

	GLM2_VEC
	inline VEC::~vec(void)
	{
	}

	GLM2_VEC
	inline VEC	&VEC::operator=(T b)
	{
		GLM2_VEC_ITER(_data[i] = b;)
		return (*this);
	}

	GLM2_VEC
	inline VEC	&VEC::operator=(const VEC& other)
	{
		if (this != &other)
			GLM2_VEC_ITER(_data[i] = other._data[i];)
		return (*this);
	}

	GLM2_VEC
	inline VEC	&VEC::operator=(const T *arr)
	{
		static_assert(sizeof(arr) == N, "Array size must match vector dimension");
		GLM2_VEC_ITER(_data[i] = arr[i];)
		return (*this);
	}

	GLM2_VEC
	inline VEC::vec(T x)
	{
		GLM2_VEC_ITER(_data[i] = x;)
	}

	GLM2_VEC
	inline VEC::vec(T x, T y)
	{
		static_assert(N == 2, "vec(x, y) is only valid for vec2");
		_data[0] = x;
		_data[1] = y;
	}

	GLM2_VEC
	inline VEC::vec(T x, T y, T z)
	{
		static_assert(N == 3, "vec(x, y, z) is only valid for vec3");
		_data[0] = x;
		_data[1] = y;
		_data[2] = z;
	}

	GLM2_VEC
	inline VEC::vec(T x, T y, T z, T w)
	{
		static_assert(N == 4, "vec(x, y, z, w) is only valid for vec4");
		_data[0] = x;
		_data[1] = y;
		_data[2] = z;
		_data[3] = w;
	}

	GLM2_VEC
	inline T	&VEC::operator[](unsigned int i)
	{
		return (_data[i]);
	}

	GLM2_VEC
	inline T const	&VEC::operator[](unsigned int i) const
	{
		return (_data[i]);
	}

	GLM2_VEC
	inline VEC	&VEC::operator*=(T b)
	{
		GLM2_VEC_ITER(_data[i] *= b;)
		return (*this);
	}

	GLM2_VEC
	inline VEC	&VEC::operator-=(const VEC& b)
	{
		GLM2_VEC_ITER(_data[i] -= b[i];)
		return (*this);
	}

	GLM2_VEC
	inline VEC	&VEC::operator+=(const VEC& b)
	{
		GLM2_VEC_ITER(_data[i] += b[i];)
		return (*this);
	}

	GLM2_VEC
	inline VEC const	&VEC::operator*=(T b) const
	{
		GLM2_VEC_ITER(_data[i] *= b;)
		return (*this);
	}

	GLM2_VEC
	inline VEC const	&VEC::operator-=(const VEC& b) const
	{
		GLM2_VEC_ITER(_data[i] -= b[i];)
		return (*this);
	}

	GLM2_VEC
	inline VEC const	&VEC::operator+=(const VEC& b) const
	{
		GLM2_VEC_ITER(_data[i] += b[i];)
		return (*this);
	}

	GLM2_VEC
	inline VEC	operator+(const VEC &a, const VEC &b)
	{
		VEC	res;

		GLM2_VEC_ITER(res[i] = a[i] + b[i];)
		return (res);
	}

	GLM2_VEC
	inline VEC	operator-(const VEC &a, const VEC &b)
	{
		VEC	res;

		GLM2_VEC_ITER(res[i] = a[i] - b[i];)
		return (res);
	}

	GLM2_VEC
	inline VEC	operator*(const VEC &a, const VEC &b)
	{
		VEC	res;

		GLM2_VEC_ITER(res[i] = a[i] * b[i];)
		return (res);
	}

	GLM2_VEC
	inline VEC	operator*(const VEC &a, T b)
	{
		VEC	res;

		GLM2_VEC_ITER(res[i] = a[i] * b;)
		return (res);
	}

	GLM2_VEC
	bool	operator==(const VEC &a, const VEC &b)
	{
		GLM2_VEC_ITER(
			if (a[i] != b[i])
				return (false);
		)
		return (true);
	}
}
