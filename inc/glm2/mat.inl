namespace glm2
{
	GLM2_MAT
	inline MAT::mat(void)
	{
		GLM2_MAT_ITER(_data[i] = VEC(T(0));)
	}

	GLM2_MAT
	inline MAT::mat(T num)
	{
		VEC	vec;

		GLM2_MAT_ITER(
			vec = T(0);
			vec[i] = num;
			_data[i] = vec;
		)
	}

	GLM2_MAT
	inline MAT::mat(const MAT &mat)
	{
		GLM2_MAT_ITER(_data[i] = mat._data[i];)
	}

	GLM2_MAT
	inline MAT &MAT::operator=(const MAT &mat)
	{
		if (this != &mat)
			GLM2_MAT_ITER(_data[i] = mat._data[i];)
		return (*this);
	}

	GLM2_MAT
	inline VEC	&MAT::operator[](unsigned int i)
	{
		return (_data[i]);
	}

	GLM2_MAT
	inline const VEC	&MAT::operator[](unsigned int i) const
	{
		return (_data[i]);
	}

	GLM2_MAT
	inline MAT::~mat(void)
	{
	}
}
