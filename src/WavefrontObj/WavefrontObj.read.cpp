#include <WavefrontObj.hpp>

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

void	WavefrontObj::read(const std::string &objPath, const std::string &mtlPath)
{
	{
		std::ifstream	objFile(objPath);
		std::string		line;
		Vertex			vert;
		uTex			tex;
		uIndex			idx;
		uIndex			texIdx;
		uIndex			normIdx;
		tMaterial		mat;

		if (!objFile.is_open())
		{
			std::cerr << "could not open file: " << objPath << std::endl;
			return ;
		}
		_vertices.clear();
		_texCoords.clear();
		_vertNorms.clear();
		_indices.clear();
		_texIndices.clear();
		_normIndices.clear();
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
			else if (word == "vt")
			{
				iss >> tex.u >> tex.v;
				_texCoords.push_back(tex);
			}
			else if (word == "vn")
			{
				iss >> vert.x >> vert.y >> vert.z;
				vert.x = -vert.x;
				vert.y = -vert.y;
				vert.z = -vert.z;
				_vertNorms.push_back(vert);
			}
			else if (word == "f")
			{
				std::string		fword[4];
				char			c;
				iss >> fword[0] >> fword[1] >> fword[2] >> fword[3];
				std::istringstream(fword[0]) >> idx.v1 >> c >> texIdx.v1 >> c >> normIdx.v1;
				std::istringstream(fword[1]) >> idx.v2 >> c >> texIdx.v2 >> c >> normIdx.v2;
				std::istringstream(fword[2]) >> idx.v3 >> c >> texIdx.v3 >> c >> normIdx.v3;
				idx.v1 -= 1;
				idx.v2 -= 1;
				idx.v3 -= 1;
				_indices.push_back(idx);
				texIdx.v1 -= 1;
				texIdx.v2 -= 1;
				texIdx.v3 -= 1;
				_texIndices.push_back(texIdx);
				normIdx.v1 -= 1;
				normIdx.v2 -= 1;
				normIdx.v3 -= 1;
				_normIndices.push_back(normIdx);
				if (fword[3].size())
				{
					idx.v2 = idx.v3;
					texIdx.v2 = texIdx.v3;
					normIdx.v2 = normIdx.v3;
					std::istringstream(fword[3]) >> idx.v3 >> c >> texIdx.v3 >> c >> normIdx.v3;
					idx.v3 -= 1;
					texIdx.v3 -= 1;
					normIdx.v3 -= 1;
					_indices.push_back(idx);
					_texIndices.push_back(texIdx);
					_normIndices.push_back(normIdx);
				}
			}
		}
		_vertexAvg.x /= _vertices.size();
		_vertexAvg.y /= _vertices.size();
		_vertexAvg.z /= _vertices.size();
	}
	{

		std::vector<Vertex>	vertices(_vertices.begin(), _vertices.end());
		std::vector<Vertex>	vertNorms(_vertNorms.begin(), _vertNorms.end());
		std::vector<Vertex>	vertNorms1(_vertices.size());
		std::list<Vertex>	vertNorms2;
		std::vector<uTex>	texCoords(_texCoords.begin(), _texCoords.end());
		std::vector<uTex>	texCoords1(_vertices.size());
		std::list<uTex>		texCoords2;
		std::list<uIndex>::iterator	itt;
		std::list<uIndex>::iterator	itn;
		
		if (_texCoords.size())
		{
			itt = _texIndices.begin();
			for (uIndex &idx : _indices)
			{
				for (unsigned int i = 0; i < 3; i++)
				{
					unsigned int	vIdx = idx.data[i];
					unsigned int	tIdx = itt->data[i];
					
					texCoords1[vIdx] = texCoords[tIdx];
				}
				itt++;
			}
		}
		
		itt = _texIndices.begin();
		itn = _normIndices.begin();
		for (uIndex &idx : _indices)
		{
			Vertex	&v1 = vertices[idx.v1];
			Vertex	&v2 = vertices[idx.v2];
			Vertex	&v3 = vertices[idx.v3];
			Vertex	normCalc;

			Vertex	edge1(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
			Vertex	edge2(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
			
			normCalc.x = edge1.y * edge2.z - edge1.z * edge2.y;
			normCalc.y = edge1.z * edge2.x - edge1.x * edge2.z;
			normCalc.z = edge1.x * edge2.y - edge1.y * edge2.x;

			for (unsigned int i = 0; i < 3; i++)
			{
				unsigned int	vIdx = idx.data[i];
				unsigned int	nIdx = itn->data[i];
				Vertex			&n = vertNorms1[vIdx];
				Vertex			norm;

				if (nIdx < vertNorms.size())
				norm = vertNorms[nIdx];
				else
					norm = normCalc;
					
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
					vertNorms2.push_back(norm);
					if (_texCoords.size())
						texCoords2.push_back(texCoords[itt->data[i]]);
				}
			}
			itt++;
			itn++;
		}
		_vertNorms.clear();
		for (Vertex &norm : vertNorms1)
			_vertNorms.push_back(norm);
		for (Vertex &norm : vertNorms2)
			_vertNorms.push_back(norm);

		for (Vertex &norm : _vertNorms)
			norm *= Q_rsqrt(dot(norm, norm));
			
		_texCoords.clear();
		for (uTex &tex : texCoords1)
			_texCoords.push_back(tex);
		for (uTex &tex : texCoords2)
			_texCoords.push_back(tex);
	}
	this->stats(objPath.c_str());
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
