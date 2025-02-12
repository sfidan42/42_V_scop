#pragma once
# include <vector>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>

class Obj
{
private:
	std::vector<float>			_vertices;
	float						_vertexAvg[3] = {0.0f, 0.0f, 0.0f};
	std::vector<unsigned int>	_indices;
public:
	Obj(void);
	~Obj();
	void						read(const char *file_path);
	std::vector<float>			get_vertices(void);
	std::vector<unsigned int>	get_indices(void);
};
