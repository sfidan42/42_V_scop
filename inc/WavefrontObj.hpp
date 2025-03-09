#pragma once
# include <vector>
# include <list>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <glm/glm.hpp>
# include "Q_rsqrt.hpp"

typedef struct
{
	std::string		name; // Wood
	glm::vec3		ka; // 1.000000 1.000000 1.000000
	glm::vec3		kd; // 0.640000 0.640000 0.640000
	glm::vec3		ks; // 0.500000 0.500000 0.500000
	float			ns; // 96.078431
	float			ni; // 1.000000
	float			d; // 1.000000
	unsigned int	illum; // 0
	std::string		map_Kd; // woodtexture.jpg
}					tMaterial;

class WavefrontObj
{
private:
	std::list<glm::vec3>			_vertices;
	std::list<glm::vec3>			_vertNorms;
	std::list<glm::vec2>			_texCoords;
	std::list<glm::vec<3, uint>>	_indices;
	std::list<glm::vec<3, uint>>	_texIndices;
	std::list<glm::vec<3, uint>>	_normIndices;
	glm::vec3						_vertexAvg;
	tMaterial						_mat;
public:
	WavefrontObj(void);
	~WavefrontObj();
	void								read(const std::string &objPath, const std::string &mtlPath);
	const std::vector<float>			getVertices(void);
	const std::vector<float>			getNormalEnds(void);
	const std::vector<unsigned int>		getIndices(void);
	const tMaterial						getMaterial(void);
	void								stats(const char *title);
};
