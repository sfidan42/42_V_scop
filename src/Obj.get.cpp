#include <Obj.hpp>

const std::vector<float>	Obj::getVertices(void)
{
	std::list<Vertex>::iterator		itv = _vertices.begin();
	std::list<Vertex>::iterator		itn = _vertNorms.begin();
	std::list<uTex>::iterator		itt = _texCoords.begin();
	std::vector<float>::iterator	it;
	std::vector<float>				vec;

	std::cout << "number of _vertices: " << _vertices.size() << std::endl;
	std::cout << "number of _vertNorms: " << _vertNorms.size() << std::endl;
	std::cout << "number of _texCoords: " << _texCoords.size() << std::endl;

	vec.resize(_vertices.size() * ((2 * sizeof(Vertex) + sizeof(uTex)) / sizeof(float)));

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
			*it++ = itt->u;
			*it++ = 1.0f - itt->v;
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
