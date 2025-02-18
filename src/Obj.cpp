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
	uVertex			vert;
	uIndex			idx;

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

std::vector<float>	Obj::getVertices(void)
{
	std::vector<float>::iterator	it;
	std::vector<float>				vec;
	uColor							col { .r = 0.7f, .g = 0.7f, .b = 0.7f };

	vec.resize(_vertices.size() * (sizeof(uVertex) + sizeof(uColor)));
	it = vec.begin();
	for (uVertex &vert : _vertices)
	{
		*it++ = vert.x - _vertexAvg.x;
		*it++ = vert.y - _vertexAvg.y;
		*it++ = vert.z - _vertexAvg.z;
		*it++ = col.r;
		*it++ = col.g;
		*it++ = col.b;
	}
	return (vec);
}

std::vector<unsigned int>	Obj::getIndices(void)
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
