#include <Obj.hpp>

const std::vector<float>	Obj::getVertices(void)
{
	std::list<Vertex>::iterator	itv = _vertices.begin();
	std::list<Vertex>::iterator	itn = _vertNorms.begin();
	std::vector<float>::iterator	it;
	std::vector<float>				vec;

	vec.resize(_vertices.size() * (3 * sizeof(Vertex) / sizeof(float)));
	for (it = vec.begin(); itv != _vertices.end(); itv++, itn++)
	{
		*it++ = itv->x - _vertexAvg.x;
		*it++ = itv->y - _vertexAvg.y;
		*it++ = itv->z - _vertexAvg.z;
		*it++ = itn->x;
		*it++ = itn->y;
		*it++ = itn->z;
		*it++ = itv->x - _vertexAvg.x - 0.1f * itn->x;
		*it++ = itv->y - _vertexAvg.y - 0.1f * itn->y;
		*it++ = itv->z - _vertexAvg.z - 0.1f * itn->z;
	}
	return (vec);
}

const std::vector<unsigned int>	Obj::getIndices(void)
{
	std::vector<unsigned int>::iterator	it;
	std::vector<unsigned int>			vec;

	vec.resize(_indices.size() * sizeof(uIndex));
	it = vec.begin();
	for (uIndex &idx : _indices)
	{
		*it++ = idx.v1;
		*it++ = idx.v2;
		*it++ = idx.v3;
	}
	return (vec);
}

const tMaterial	Obj::getMaterial(void)
{
	return (_mat);
}
