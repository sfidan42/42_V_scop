#include <Obj.hpp>

Obj::Obj(void) : _vertexAvg{0.0f, 0.0f, 0.0f}
{
	_mat.kd = { .r = 1.0f, .g = 1.0f, .b = 1.0f };
	_mat.ka = { .r = 0.1f, .g = 0.1f, .b = 0.1f };
	_mat.ks = { .r = 0.7f, .g = 0.7f, .b = 0.7f };
}

Obj::~Obj()
{
}

static int	sameNormal(const uVertex &n1, const uVertex &n2)
{
	return (n1.x == n2.x && n1.y == n2.y && n1.z == n2.z);
}

static int	zerosNormal(const uVertex &n)
{
	return (n.x == 0.0f && n.y == 0.0f && n.z == 0.0f);
}

void	Obj::read(const std::string objPath, const std::string mtlPath)
{
	{
		std::ifstream	objFile(objPath);
		std::string		line;
		uVertex			vert;
		tMaterial		mat;
		tIndex			idx;

		if (!objFile.is_open())
		{
			std::cerr << "could not open file: " << objPath << std::endl;
			return ;
		}
		_vertices.clear();
		_indices.clear();
		while (std::getline(objFile, line))
		{
			std::istringstream	iss(line);
			std::string			word;
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
				std::string		fword[4];
				iss >> fword[0] >> fword[1] >> fword[2] >> fword[3];
				std::istringstream(fword[0]) >> idx.v1;
				std::istringstream(fword[1]) >> idx.v2;
				std::istringstream(fword[2]) >> idx.v3;
				idx.v1 -= 1;
				idx.v2 -= 1;
				idx.v3 -= 1;
				_indices.push_back(idx);
				if (fword[3].size())
				{
					std::istringstream(fword[3]) >> idx.v2;
					idx.v2 -= 1;
					_indices.push_back(idx);
				}
			}
		}
		_vertexAvg.x /= _vertices.size();
		_vertexAvg.y /= _vertices.size();
		_vertexAvg.z /= _vertices.size();
		std::cout << "\tnumber of _vertices: " << _vertices.size() << std::endl;
		std::cout << "\tnumber of _indices: " << _indices.size() << std::endl;
		std::cout << "\tsize of the object: " << (float)(_vertices.size() * sizeof(uVertex) +
												(float)(_vertNorms.size() * sizeof(uVertex)) +
												_indices.size() * sizeof(tIndex))
												/ 1024.0f << "kB" << std::endl;
		std::cout << "\taverage of vertices: " << _vertexAvg.x << " " << _vertexAvg.y << " " << _vertexAvg.z << " " << std::endl;
	}
	{
		std::vector<uVertex>	vertices(_vertices.begin(), _vertices.end());
		std::vector<uVertex>	vertNorms(_vertices.size(), { .x = 0.0f, .y = 0.0f, .z = 0.0f });
		std::list<uVertex>		vertNormsP2;

		for (tIndex &idx : _indices)
		{
			uVertex	&v1 = vertices[idx.v1];
			uVertex	&v2 = vertices[idx.v2];
			uVertex	&v3 = vertices[idx.v3];
			uVertex	&n1 = vertNorms[idx.v1];
			uVertex	&n2 = vertNorms[idx.v2];
			uVertex	&n3 = vertNorms[idx.v3];
			uVertex	norm;

			uVertex	edge1 = { .x = v3.x - v1.x, .y = v3.y - v1.y, .z = v3.z - v1.z };
			uVertex	edge2 = { .x = v2.x - v1.x, .y = v2.y - v1.y, .z = v2.z - v1.z };

			norm.x = edge1.y * edge2.z - edge1.z * edge2.y;
			norm.y = edge1.z * edge2.x - edge1.x * edge2.z;
			norm.z = edge1.x * edge2.y - edge1.y * edge2.x;

			float	length = sqrtf(norm.x * norm.x + norm.y * norm.y + norm.z * norm.z);
			norm.x /= length;
			norm.y /= length;
			norm.z /= length;

			if (zerosNormal(n1))
				n1 = norm;
			else if (!sameNormal(n1, norm))
			{
				idx.v1 = (unsigned int)_vertices.size();
				_vertices.push_back(v1);
				vertNormsP2.push_back(norm);
			}

			if (zerosNormal(n2))
				n2 = norm;
			else if (!sameNormal(n2, norm))
			{
				idx.v2 = (unsigned int)_vertices.size();
				_vertices.push_back(v2);
				vertNormsP2.push_back(norm);
			}

			if (zerosNormal(n3))
				n3 = norm;
			else if (!sameNormal(n3, norm))
			{
				idx.v3 = (unsigned int)_vertices.size();
				_vertices.push_back(v3);
				vertNormsP2.push_back(norm);
			}
		}

		_vertNorms.clear();
		for (uVertex &norm : vertNorms)
			_vertNorms.push_back(norm);
		for (uVertex &norm : vertNormsP2)
			_vertNorms.push_back(norm);

		std::cout << "After computing normals" << std::endl;
		std::cout << "\tnumber of _vertices: " << _vertices.size() << std::endl;
		std::cout << "\tnumber of _vertNorms: " << _vertNorms.size() << std::endl;
		std::cout << "\tnumber of _indices: " << _indices.size() << std::endl;
		std::cout << "\tsize of the object: " << (float)(_vertices.size() * sizeof(uVertex) +
												(float)(_vertNorms.size() * sizeof(uVertex)) +
												_indices.size() * sizeof(tIndex))
												/ 1024.0f << "kB" << std::endl;
		//{
		//	std::vector<uVertex>	newVertNorms(_vertNorms.begin(), _vertNorms.end());
		//	std::vector<uVertex>	newVertices(_vertices.begin(), _vertices.end());
		//	for (tIndex &idx : _indices)
		//	{
		//		uVertex &n1 = newVertNorms[idx.v1];
		//		uVertex &n2 = newVertNorms[idx.v2];
		//		uVertex &n3 = newVertNorms[idx.v3];
		//		uVertex &v1 = newVertices[idx.v1];
		//		uVertex &v2 = newVertices[idx.v2];
		//		uVertex &v3 = newVertices[idx.v3];
		//		std::cout << "Face:" << std::endl;
		//		std::cout << "\t[" << n1.x << "," << n1.y << "," << n1.z << "]\t(" << v1.x << "," << v1.y << "," << v1.z << ")" << std::endl;
		//		std::cout << "\t[" << n2.x << "," << n2.y << "," << n2.z << "]\t(" << v2.x << "," << v2.y << "," << v2.z << ")" << std::endl;
		//		std::cout << "\t[" << n3.x << "," << n3.y << "," << n3.z << "]\t(" << v3.x << "," << v3.y << "," << v3.z << ")" << std::endl;
		//	}
		//}
		}
	{
		std::ifstream	mtlFile(mtlPath);
		std::string		line;

		if (!mtlFile.is_open())
		{
			std::cout << "could not open .mtl file" << std::endl;
			std::cout << "using the default material" << std::endl;
			return ;
		}
		while (getline(mtlFile, line))
		{
			if (line.size() == 0)
				continue ;
			std::istringstream	iss(line);
			std::string			word;
			iss >> word;

			if (word == "newmtl")
			{
				iss >> _mat.name;
			}
			else if (word == "Kd")
			{
				iss >> _mat.kd.r >> _mat.kd.g >> _mat.kd.b;
			}
			else if (word == "Ka")
			{
				iss >> _mat.ka.r >> _mat.ka.g >> _mat.ka.b;
			}
			else if (word == "Ks")
			{
				iss >> _mat.ks.r >> _mat.ks.g >> _mat.ks.b;
			}
			else if (word == "Ns")
			{
				iss >> _mat.ns;
			}
			else if (word == "Ni")
			{
				iss >> _mat.ni;
			}
			else if (word == "d")
			{
				iss >> _mat.d;
			}
			else if (word == "illum")
			{
				iss >> _mat.illum;
			}
		}
	}
}

const std::vector<float>	Obj::getVertices(void)
{
	std::list<uVertex>::iterator	itv = _vertices.begin();
	std::list<uVertex>::iterator	itn = _vertNorms.begin();
	std::vector<float>::iterator	it;
	std::vector<float>				vec;

	vec.resize(_vertices.size() * (2 * sizeof(uVertex) / sizeof(float)));
	for (it = vec.begin(); itv != _vertices.end(); itv++, itn++)
	{
		*it++ = itv->x - _vertexAvg.x;
		*it++ = itv->y - _vertexAvg.y;
		*it++ = itv->z - _vertexAvg.z;
		*it++ = itn->x;
		*it++ = itn->y;
		*it++ = itn->z;
	}
	return (vec);
}

const std::vector<unsigned int>	Obj::getIndices(void)
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

const tMaterial	Obj::getMaterial(void)
{
	return (_mat);
}
