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
	vertex			vert;
	triangle		tri;

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
			iss >> tri.v1 >> tri.v2 >> tri.v3;
			tri.data[0] -= 1;
			tri.data[1] -= 1;
			tri.data[2] -= 1;
			_indices.push_back(tri);
		}
	}
	_vertexAvg.x /= _vertices.size();
	_vertexAvg.y /= _vertices.size();
	_vertexAvg.z /= _vertices.size();
	std::cout << "size of vertices: " << _vertices.size() << std::endl;
	std::cout << "size of indices: " << _indices.size() << std::endl;
	std::cout << "size of the object: " << (float)(_vertices.size() * sizeof(float) + _indices.size() * sizeof(unsigned int)) / 1024.0f << "kB" << std::endl;
	std::cout << "average of vertices: " << _vertexAvg.x << " " << _vertexAvg.y << " " << _vertexAvg.z << " " << std::endl;
}

std::vector<float>	Obj::getVertices(void)
{
	std::vector<float>::iterator	it;
	std::vector<float>				vec;

	vec.resize(_vertices.size() * sizeof(vertex));
	it = vec.begin();
	for (vertex &vert : _vertices)
	{
		*it++ = vert.x;
		*it++ = vert.y;
		*it++ = vert.z;
		*it++ = 0.7f;
		*it++ = 0.7f;
		*it++ = 0.7f;
	}
	return (vec);
}

std::vector<unsigned int>	Obj::getIndices(void)
{
	std::vector<unsigned int>::iterator	it;
	std::vector<unsigned int>			vec;

	vec.resize(_indices.size() * sizeof(triangle));
	it = vec.begin();
	for (triangle &tri : _indices)
	{
		*it++ = tri.v1;
		*it++ = tri.v2;
		*it++ = tri.v3;
	}
	return (vec);
}

vertex	Obj::getVertexAvg(void)
{
	return	(_vertexAvg);
}
