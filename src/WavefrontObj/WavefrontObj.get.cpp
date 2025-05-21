#include <WavefrontObj.hpp>

const vector<float>	WavefrontObj::getVertices(void)
{
	auto	itv = _vertices.begin();
	auto	itn = _vertNorms.begin();
	auto	itt = _texCoords.begin();

	vector<float>	vec(_vertices.size() * 8);

	for (auto it = vec.begin(); itv != _vertices.end(); itv++, itn++, itt++)
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
	return (vec);
}

const vector<unsigned int>	WavefrontObj::getIndices(void)
{
	vector<unsigned int>	vec(_indices.size() * 3);

	auto it = vec.begin();
	for (auto &idx : _indices)
	{
		*it++ = idx.x;
		*it++ = idx.y;
		*it++ = idx.z;
	}
	return (vec);
}

const tMaterial	&WavefrontObj::getMaterial(void)
{
	return (_mat);
}
