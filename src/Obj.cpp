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

static int	fcmp(float f1, float f2)
{
	return (fabs(f1 - f2) < 0.001f);
}

static float sameNormals(const Vertex &n1, const Vertex &n2)
{
	return (fcmp(n1.x, n2.x) && fcmp(n1.y, n2.y) && fcmp(n1.z, n2.z));
}

static int	zerosNormal(const Vertex &n)
{
	return (fcmp(n.x, 0.0f) && fcmp(n.y, 0.0f) && fcmp(n.z, 0.0f));
}

static void	normalizeVertex(Vertex &v)
{
	float	len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	v.x /= len;
	v.y /= len;
	v.z /= len;
}

void	Obj::read(const std::string objPath, const std::string mtlPath)
{
	{
		std::ifstream	objFile(objPath);
		std::string		line;
		Vertex			vert;
		tMaterial		mat;
		uIndex			idx;

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
		std::cout << "\tsize of the object: " << (float)(_vertices.size() * sizeof(Vertex) +
												(_vertNorms.size() * sizeof(Vertex)) +
												_indices.size() * sizeof(uIndex))
												/ 1024.0f << "kB" << std::endl;
		std::cout << "\taverage of vertices: " << _vertexAvg.x << " " << _vertexAvg.y << " " << _vertexAvg.z << " " << std::endl;
	}
	{
		std::vector<Vertex>	vertices(_vertices.begin(), _vertices.end());
		std::vector<Vertex>	vertNorms(_vertices.size());
		std::list<Vertex>	vertNormsP2;

		for (uIndex &idx : _indices)
		{
			Vertex	&v1 = vertices[idx.v1];
			Vertex	&v2 = vertices[idx.v2];
			Vertex	&v3 = vertices[idx.v3];
			Vertex	norm;

			Vertex	edge1(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
			Vertex	edge2(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);

			norm.x = edge1.y * edge2.z - edge1.z * edge2.y;
			norm.y = edge1.z * edge2.x - edge1.x * edge2.z;
			norm.z = edge1.x * edge2.y - edge1.y * edge2.x;

			for (unsigned int i = 0; i < 3; i++)
			{
				uint	vIdx = idx.data[i];
				Vertex	&n = vertNorms[vIdx];

				if (zerosNormal(n))
				{
					n = norm;
					continue ;
				}

				int same = sameNormals(n, norm);

				if (!same)
				{
					idx.data[i] = (unsigned int)_vertices.size();
					_vertices.push_back(vertices[vIdx]);
					vertNormsP2.push_back(norm);
				}
			}
		}

		_vertNorms.clear();
		for (Vertex &norm : vertNorms)
			_vertNorms.push_back(norm);
		for (Vertex &norm : vertNormsP2)
			_vertNorms.push_back(norm);

		for (Vertex &norm : _vertNorms)
			normalizeVertex(norm);

		std::cout << "After computing normals" << std::endl;
		std::cout << "\tnumber of _vertices: " << _vertices.size() << std::endl;
		std::cout << "\tnumber of _vertNorms: " << _vertNorms.size() << std::endl;
		std::cout << "\tnumber of _indices: " << _indices.size() << std::endl;
		std::cout << "\tsize of the object: " << (float)(_vertices.size() * sizeof(Vertex) +
												(_vertNorms.size() * sizeof(Vertex)) +
												_indices.size() * sizeof(uIndex))
												/ 1024.0f << "kB" << std::endl;
		//{
		//	std::vector<Vertex>	newVertNorms(_vertNorms.begin(), _vertNorms.end());
		//	std::vector<Vertex>	newVertices(_vertices.begin(), _vertices.end());
		//	for (uIndex &idx : _indices)
		//	{
		//		Vertex &n1 = newVertNorms[idx.v1];
		//		Vertex &n2 = newVertNorms[idx.v2];
		//		Vertex &n3 = newVertNorms[idx.v3];
		//		Vertex &v1 = newVertices[idx.v1];
		//		Vertex &v2 = newVertices[idx.v2];
		//		Vertex &v3 = newVertices[idx.v3];
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
				iss >> _mat.name;
			else if (word == "Kd")
				iss >> _mat.kd.r >> _mat.kd.g >> _mat.kd.b;
			else if (word == "Ka")
				iss >> _mat.ka.r >> _mat.ka.g >> _mat.ka.b;
			else if (word == "Ks")
				iss >> _mat.ks.r >> _mat.ks.g >> _mat.ks.b;
			else if (word == "Ns")
				iss >> _mat.ns;
			else if (word == "Ni")
				iss >> _mat.ni;
			else if (word == "d")
				iss >> _mat.d;
			else if (word == "illum")
				iss >> _mat.illum;
			else
				std::cout << "unknown word: " << word << std::endl;
		}
	}
}

const std::vector<float>	Obj::getVertices(void)
{
	std::list<Vertex>::iterator	itv = _vertices.begin();
	std::list<Vertex>::iterator	itn = _vertNorms.begin();
	std::vector<float>::iterator	it;
	std::vector<float>				vec;

	vec.resize(_vertices.size() * (3 * sizeof(Vertex) / sizeof(float)));
	for (it = vec.begin(); itv != _vertices.end(); itv++, itn++)
	{
		*it++ = itv->x - _vertexAvg.x;
		*it++ = itv->y - _vertexAvg.y;
		*it++ = itv->z - _vertexAvg.z;
		*it++ = itn->x;
		*it++ = itn->y;
		*it++ = itn->z;
		*it++ = itv->x - _vertexAvg.x - 0.1f * itn->x;
		*it++ = itv->y - _vertexAvg.y - 0.1f * itn->y;
		*it++ = itv->z - _vertexAvg.z - 0.1f * itn->z;
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
