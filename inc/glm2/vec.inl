namespace glm2
{
    template <unsigned int N, typename T>
    vec<N, T>::vec(void)
    {
        _data.fill(T());
    }

    template <unsigned int N, typename T>
    vec<N, T>::vec(const vec<N, T>& other)
    {
        for (unsigned int i = 0; i < N; ++i)
            _data[i] = other._data[i];
    }

    template <unsigned int N, typename T>
    vec<N, T>::~vec(void)
    {
    }

    template <unsigned int N, typename T>
    vec<N, T>& vec<N, T>::operator=(const vec<N, T>& other)
    {
        if (this != &other)
        {
            for (unsigned int i = 0; i < N; ++i)
                _data[i] = other._data[i];
        }
        return *this;
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
    vec<N, T>& vec<N, T>::operator=(Args... args)
    {
        static_assert(sizeof...(Args) == N, "Number of arguments must match vector dimension");
        std::array<T, N> tempArray = {static_cast<T>(args)...};
        _data = tempArray;
        return *this;
    }

    template <unsigned int N, typename T>
    T& vec<N, T>::operator[](int i)
    {
        return _data[i];
    }

    template <unsigned int N, typename T>
    const T& vec<N, T>::operator[](int i) const
    {
        return _data[i];
    }
}
