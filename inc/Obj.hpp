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
