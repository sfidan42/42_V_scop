#pragma once
# include <vector>
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <cmath>

typedef union
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	float		data[3];
}				uVertex;

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
	std::list<uVertex>	_vertices;
	std::list<tIndex>	_indices;
	std::list<uVertex>	_vertNorms;
	uVertex				_vertexAvg;
	tMaterial			_mat;
public:
	Obj(void);
	~Obj();
	void						read(const std::string objPath, const std::string mtlPath);
	const std::vector<float>			getVertices(void);
	const std::vector<unsigned int>		getIndices(void);
	const tMaterial						getMaterial(void);
};
