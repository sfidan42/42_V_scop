#include <WavefrontObj.hpp>

const std::vector<float>	WavefrontObj::getVertices(void)
{
	std::list<glm::vec3>::iterator		itv = _vertices.begin();
	std::list<glm::vec3>::iterator		itn = _vertNorms.begin();
	std::list<glm::vec2>::iterator		itt = _texCoords.begin();
	std::vector<float>::iterator	it;
	std::vector<float>				vec;

	vec.resize(_vertices.size() * ((2 * sizeof(glm::vec3) + sizeof(glm::vec2)) / sizeof(float)));

	if (_texCoords.size())
	{
		for (it = vec.begin(); itv != _vertices.end(); itv++, itn++, itt++)
		{
			*it++ = itv->x - _vertexAvg.x;
			*it++ = itv->y - _vertexAvg.y;
			*it++ = itv->z - _vertexAvg.z;
			*it++ = itn->x;
			*it++ = itn->y;
			*it++ = itn->z;
			*it++ = itt->x;
			*it++ = itt->y;
		}
	}
	else
	{
		for (it = vec.begin(); itv != _vertices.end(); itv++, itn++)
		{
			*it++ = itv->x - _vertexAvg.x;
			*it++ = itv->y - _vertexAvg.y;
			*it++ = itv->z - _vertexAvg.z;
			*it++ = itn->x;
			*it++ = itn->y;
			*it++ = itn->z;
			*it++ = 0.0f;
			*it++ = 0.0f;
		}
	}
	return (vec);
}

const std::vector<unsigned int>	WavefrontObj::getIndices(void)
{
	std::vector<unsigned int>::iterator	it;
	std::vector<unsigned int>			vec;

	vec.resize(_indices.size() * sizeof(glm::vec<3, uint>));
	it = vec.begin();
	for (glm::vec<3, uint> &idx : _indices)
	{
		*it++ = idx.x;
		*it++ = idx.y;
		*it++ = idx.z;
	}
	return (vec);
}

const tMaterial	WavefrontObj::getMaterial(void)
{
	return (_mat);
}
