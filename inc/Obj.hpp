#pragma once
# include <vector>
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <cmath>
# include "Vertex.hpp"

typedef struct
{
	float	r;
	float	g;
	float	b;
}			tColor;

typedef union
{
	struct
	{
		unsigned int	v1;
		unsigned int	v2;
		unsigned int	v3;
	};
	unsigned int		data[3];
}						uIndex;

typedef struct
{
	std::string		name; // Wood
	tColor			ka; // 1.000000 1.000000 1.000000
	tColor			kd; // 0.640000 0.640000 0.640000
	tColor			ks; // 0.500000 0.500000 0.500000
	float			ns; // 96.078431
	float			ni; // 1.000000
	float			d; // 1.000000
	unsigned int	illum; // 0
	std::string		map_Kd; // woodtexture.jpg
}					tMaterial;

class Obj
{
private:
	std::list<Vertex>	_vertices;
	std::list<uIndex>	_indices;
	std::list<Vertex>	_vertNorms;
	Vertex				_vertexAvg;
	tMaterial			_mat;
public:
	Obj(void);
	~Obj();
	void								read(const std::string objPath, const std::string mtlPath);
	const std::vector<float>			getVertices(void);
	const std::vector<float>			getNormalEnds(void);
	const std::vector<unsigned int>		getIndices(void);
	const tMaterial						getMaterial(void);
};
