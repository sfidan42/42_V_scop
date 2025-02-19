#include <Obj.hpp>

Obj::Obj(void) : _vertexAvg{0.0f, 0.0f, 0.0f}
{
}

Obj::~Obj()
{
}

void	Obj::read(const char *file_path)
{
	std::ifstream	file(file_path);
	std::string		line;
	std::string		word;
	tVertex			vert;
	tIndex			idx;

	_vertices.clear();
	_indices.clear();
	while (std::getline(file, line))
	{
		std::istringstream	iss(line);
		iss >> word;
		if (word == "v")
		{
			iss >> vert.x >> vert.y >> vert.z;
			_vertices.push_back(vert);
			_vertexAvg.x += vert.x;
			_vertexAvg.y += vert.y;
			_vertexAvg.z += vert.z;
		}
		else if (word == "f")
		{
			std::string		fword[3];
			iss >> fword[0] >> fword[1] >> fword[2];
			std::istringstream(fword[0]) >> idx.v1;
			std::istringstream(fword[1]) >> idx.v2;
			std::istringstream(fword[2]) >> idx.v3;
			//iss >> idx.v1 >> idx.v2 >> idx.v3;
			idx.v1 -= 1;
			idx.v2 -= 1;
			idx.v3 -= 1;
			_indices.push_back(idx);
		}
		word.clear();
	}
	_vertexAvg.x /= _vertices.size();
	_vertexAvg.y /= _vertices.size();
	_vertexAvg.z /= _vertices.size();
	std::cout << "number of vertices: " << _vertices.size() << std::endl;
	std::cout << "number of indices: " << _indices.size() << std::endl;
	std::cout << "size of the object: " << (float)(_vertices.size() * sizeof(float) + _indices.size() * sizeof(unsigned int)) / 1024.0f << "kB" << std::endl;
	std::cout << "average of vertices: " << _vertexAvg.x << " " << _vertexAvg.y << " " << _vertexAvg.z << " " << std::endl;
}

void	Obj::findVertexNormals(void)
{
	std::vector<tIndex>		indices(_indices.begin(), _indices.end());
	std::vector<tVertex>	vertices(_vertices.begin(), _vertices.end());

	std::vector<tVertex>	triangleNormals(indices.size());
	std::vector<tVertex>	vertexNormals(vertices.size());
	std::vector<int>		vertexCount(vertices.size(), 0);

	for (size_t i = 0; i < indices.size(); i++)
	{
		tIndex	&idx = indices[i];
		tVertex	&v1 = vertices[idx.v1];
		tVertex	&v2 = vertices[idx.v2];
		tVertex	&v3 = vertices[idx.v3];
		tVertex	&normal = triangleNormals[i];

		tVertex	edge1 = { .x = v2.x - v1.x, .y = v2.y - v1.y, .z = v2.z - v1.z };
		tVertex	edge2 = { .x = v3.x - v1.x, .y = v3.y - v1.y, .z = v3.z - v1.z };

		normal.x = edge1.y * edge2.z - edge1.z * edge2.y;
		normal.y = edge1.z * edge2.x - edge1.x * edge2.z;
		normal.z = edge1.x * edge2.y - edge1.y * edge2.x;

		float	length = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
		normal.x /= length;
		normal.y /= length;
		normal.z /= length;

		vertexNormals[idx.v1].x += normal.x;
		vertexNormals[idx.v1].y += normal.y;
		vertexNormals[idx.v1].z += normal.z;

		vertexNormals[idx.v2].x += normal.x;
		vertexNormals[idx.v2].y += normal.y;
		vertexNormals[idx.v2].z += normal.z;
		
		vertexNormals[idx.v3].x += normal.x;
		vertexNormals[idx.v3].y += normal.y;
		vertexNormals[idx.v3].z += normal.z;

		vertexCount[idx.v1]++;
		vertexCount[idx.v2]++;
		vertexCount[idx.v3]++;
	}

	for (size_t i = 0; i < vertexNormals.size(); i++)
	{
		tVertex	&normal = vertexNormals[i];
		float	count = vertexCount[i];

		normal.x /= count;
		normal.y /= count;
		normal.z /= count;

	}

	_vertexNormals = vertexNormals;

}

std::vector<float>	Obj::getVertices(void)
{
	std::vector<float>::iterator	it;
	std::vector<float>				vec;
	tColor							col { .r = 0.7f, .g = 0.7f, .b = 0.7f };

	vec.resize(_vertices.size() * (2 * sizeof(tVertex) + sizeof(tColor)));
	it = vec.begin();
	unsigned int i = 0;
	this->findVertexNormals();
	for (tVertex &vert : _vertices)
	{
		*it++ = vert.x - _vertexAvg.x;
		*it++ = vert.y - _vertexAvg.y;
		*it++ = vert.z - _vertexAvg.z;
		*it++ = col.r;
		*it++ = col.g;
		*it++ = col.b;
		*it++ = _vertexNormals[i].x;
		*it++ = _vertexNormals[i].y;
		*it++ = _vertexNormals[i].z;
		i++;
	}
	return (vec);
}

std::vector<unsigned int>	Obj::getIndices(void)
{
	std::vector<unsigned int>::iterator	it;
	std::vector<unsigned int>			vec;

	vec.resize(_indices.size() * sizeof(tIndex));
	it = vec.begin();
	for (tIndex &idx : _indices)
	{
		*it++ = idx.v1;
		*it++ = idx.v2;
		*it++ = idx.v3;
	}
	return (vec);
}
