#pragma once

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
	Vertex &operator=(const Vertex &other);
	~Vertex(void);
};

Vertex operator+(const Vertex &a, const Vertex &b);
