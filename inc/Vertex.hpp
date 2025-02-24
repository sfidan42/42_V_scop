#pragma once
# include <cmath>

class Vertex
{
public:
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
		};
		float		data[3];
	};
	Vertex(void);
	Vertex(const Vertex &other);
	Vertex(float x, float y, float z);
	Vertex	&operator=(const Vertex &other);
	Vertex	&operator+=(const Vertex &other);
	Vertex	&operator=(float num);
	Vertex	&operator+=(float num);
	Vertex	&operator*=(float num);
	~Vertex(void);
};

Vertex	operator+(const Vertex &a, const Vertex &b);
bool	operator==(const Vertex &a, const Vertex &b);
bool	operator!=(const Vertex &a, const Vertex &b);
Vertex	operator+(const Vertex &a, float num);
bool	operator==(const Vertex &a, float num);
bool	operator!=(const Vertex &a, float num);
float	dot(const Vertex &a, const Vertex &b);
