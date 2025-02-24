#include <Obj.hpp>

static float	Q_rsqrt( float y )
{
	long i;
	float x2;
	const float threehalfs = 1.5F;

	x2 = y * 0.5F;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

static int	similarity(const Vertex &v1, const Vertex &v2)
{
	float   ans;

	ans = dot(v1, v2);
	ans *= Q_rsqrt(dot(v1, v1));
	ans *= Q_rsqrt(dot(v2, v2));
	ans = acosf(ans);
	ans *= 180.0f / M_PI;
	return (ans < 30.0f);
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
					idx.v2 = idx.v3;
					std::istringstream(fword[3]) >> idx.v3;
					idx.v3 -= 1;
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

				if (n == 0.0f)
				{
					n = norm;
				}
				else if (n == norm)
				{
					// do nothing
				}
				else if (similarity(n, norm))
				{
					n += norm;
				}
				else
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
			norm *= Q_rsqrt(dot(norm, norm));

		std::cout << "After computing normals" << std::endl;
		std::cout << "\tnumber of _vertices: " << _vertices.size() << std::endl;
		std::cout << "\tnumber of _vertNorms: " << _vertNorms.size() << std::endl;
		std::cout << "\tnumber of _indices: " << _indices.size() << std::endl;
		std::cout << "\tsize of the object: " << (_vertices.size() * sizeof(Vertex) +
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
