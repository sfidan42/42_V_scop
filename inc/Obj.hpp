#pragma once
# include <vector>
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>

typedef union
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	float		data[3];
}				vertex;


typedef union
{
	struct
	{
		float	r;
		float	g;
		float	b;
	};
	float		data[3];
}				color;

typedef union
{
	struct
	{
		unsigned int	v1;
		unsigned int	v2;
		unsigned int	v3;
	};
	unsigned int		data[3];
}						triangle;

class Obj
{
private:
	std::list<vertex>	_vertices;
	vertex				_vertexAvg;
	std::list<triangle>	_indices;
public:
	Obj(void);
	~Obj();
	void						read(const char *file_path);
	std::vector<float>			getVertices(void);
	std::vector<unsigned int>	getIndices(void);
};
