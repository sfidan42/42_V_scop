#include <Obj.hpp>

Obj::Obj(void)
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
	float			vertex[3];
	unsigned int	index[3];
	bool			black = true;

	_vertices.clear();
	_indices.clear();
	while (std::getline(file, line))
	{
		std::istringstream	iss(line);
		iss >> word;
		if (word == "v")
		{
			iss >> vertex[0] >> vertex[1] >> vertex[2];
			_vertices.push_back(vertex[0]);
			_vertices.push_back(vertex[1]);
			_vertices.push_back(vertex[2]);
			if (black)
			{
				_vertices.push_back(0.1f);
				_vertices.push_back(0.1f);
				_vertices.push_back(0.1f);
				black = false;
			}
			else
			{
				_vertices.push_back(1.0f);
				_vertices.push_back(1.0f);
				_vertices.push_back(1.0f);
				black = true;
			}
			_vertexAvg[0] += vertex[0];
			_vertexAvg[1] += vertex[1];
			_vertexAvg[2] += vertex[2];
		}
		else if (word == "f")
		{
			iss >> index[0] >> index[1] >> index[2];
			_indices.push_back(index[0] - 1);
			_indices.push_back(index[1] - 1);
			_indices.push_back(index[2] - 1);
		}
	}
	_vertexAvg[0] /= (_vertices.size() / 6);
	_vertexAvg[1] /= (_vertices.size() / 6);
	_vertexAvg[2] /= (_vertices.size() / 6);
	std::cout << "size of vertices: " << _vertices.size() << std::endl;
	std::cout << "size of indices: " << _indices.size() << std::endl;
	std::cout << "size of the object: " << (float)(_vertices.size() * sizeof(float) + _indices.size() * sizeof(unsigned int)) / 1024.0f << "kB" << std::endl;
	std::cout << "average of vertices: " << _vertexAvg[0] << " " << _vertexAvg[1] << " " << _vertexAvg[2] << std::endl;
}

std::vector<float>	Obj::get_vertices(void)
{
	for (unsigned int i = 0; i < _vertices.size(); i += 6)
	{
		_vertices[i] -= _vertexAvg[0];
		_vertices[i + 1] -= _vertexAvg[1];
		_vertices[i + 2] -= _vertexAvg[2];
	}
	return _vertices;
}

std::vector<unsigned int>	Obj::get_indices(void)
{
	return _indices;
}
