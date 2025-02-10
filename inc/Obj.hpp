#pragma once
# include <vector>
# include <fstream>
# include <sstream>

class Obj
{
private:
	std::vector<float>			_vertices;
	std::vector<unsigned int>	_indices;
public:
	Obj(void);
	~Obj();
	void						read(const char *file_path);
	std::vector<float>			get_vertices(void);
	std::vector<unsigned int>	get_indices(void);
};

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
	float			index[3];

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
		}
		else if (word == "f")
		{
			iss >> index[0] >> index[1] >> index[2];
			_indices.push_back(index[0]);
			_indices.push_back(index[1]);
			_indices.push_back(index[2]);
		}
	}
}

std::vector<float>	Obj::get_vertices(void)
{
	return (_vertices);
}

std::vector<unsigned int>	Obj::get_indices(void)
{
	return (_indices);
}
