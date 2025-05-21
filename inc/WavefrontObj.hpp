#pragma once
# include <vector>
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <cmath>
# include "glm2/vec.hpp"
# include "glm2/mat.hpp"
# include "glm2/transform.hpp"

using namespace glm2;
using namespace std;

typedef struct
{
	vec3			ka;		// 1.000000 1.000000 1.000000
	vec3			kd;		// 0.640000 0.640000 0.640000
	vec3			ks;		// 0.500000 0.500000 0.500000
	float			ns;		// 96.078431
	float			ni;		// 1.000000
	float			d;		// 1.000000
	unsigned int	illum;	// 0
}					tMaterial;

class WavefrontObj
{
private:
	list<vec3>			_vertices;
	list<vec3>			_vertNorms;
	list<vec2>			_texCoords;
	list<vec<3, uint>>	_indices;
	list<vec<3, uint>>	_texIndices;
	list<vec<3, uint>>	_normIndices;
	vec3				_vertexAvg;
	tMaterial			_mat;
public:
	WavefrontObj(void);
	~WavefrontObj();
	void						read(const string &objPath, const string &mtlPath);
	const vector<float>			getVertices(void);
	const vector<float>			getNormalEnds(void);
	const vector<unsigned int>	getIndices(void);
	const tMaterial				&getMaterial(void);
	void						stats(const char *title);
};
