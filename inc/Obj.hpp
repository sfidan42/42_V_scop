#pragma once
# include <vector>
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <cmath>

typedef struct
{
	float	x;
	float	y;
	float	z;
}			tVertex;

typedef struct
{
	float	r;
	float	g;
	float	b;
}			tColor;

typedef struct
{
	unsigned int	v1;
	unsigned int	v2;
	unsigned int	v3;
}					tIndex;

class Obj
{
private:
	std::list<tVertex>		_vertices;
	tVertex					_vertexAvg;
	std::list<tIndex>		_indices;
	std::vector<tVertex>	_vertexNormals;
public:
	Obj(void);
	~Obj();
	void						read(const char *file_path);
	std::vector<float>			getVertices(void);
	std::vector<unsigned int>	getIndices(void);
	void						findVertexNormals(void);
};
