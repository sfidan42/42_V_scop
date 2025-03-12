#include <WavefrontObj.hpp>

static int	similarity(const glm::vec3 &v1, const glm::vec3 &v2)
{
	float	ans;

	ans = glm2::dot(v1, v2);
	ans *= Q_rsqrt(glm2::dot(v1, v1));
	ans *= Q_rsqrt(glm2::dot(v2, v2));
	ans = acosf(ans);
	ans *= 180.0f / M_PI;
	return (ans < 30.0f);
}

void	WavefrontObj::read(const std::string &objPath, const std::string &mtlPath)
{
	{
		std::ifstream	objFile(objPath);
		std::string		line;
		glm::vec3			vert;
		glm::vec2			tex;
		glm::vec<3, uint>			idx;
		glm::vec<3, uint>			texIdx;
		glm::vec<3, uint>			normIdx;
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
				iss >> tex.x >> tex.y;
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
				std::istringstream(fword[0]) >> idx.x >> c >> texIdx.x >> c >> normIdx.x;
				std::istringstream(fword[1]) >> idx.y >> c >> texIdx.y >> c >> normIdx.y;
				std::istringstream(fword[2]) >> idx.z >> c >> texIdx.z >> c >> normIdx.z;
				idx.x -= 1;
				idx.y -= 1;
				idx.z -= 1;
				_indices.push_back(idx);
				texIdx.x -= 1;
				texIdx.y -= 1;
				texIdx.z -= 1;
				_texIndices.push_back(texIdx);
				normIdx.x -= 1;
				normIdx.y -= 1;
				normIdx.z -= 1;
				_normIndices.push_back(normIdx);
				if (fword[3].size())
				{
					idx.y = idx.z;
					texIdx.y = texIdx.z;
					normIdx.y = normIdx.z;
					std::istringstream(fword[3]) >> idx.z >> c >> texIdx.z >> c >> normIdx.z;
					idx.z -= 1;
					texIdx.z -= 1;
					normIdx.z -= 1;
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
	std::vector<glm::vec3>	vertices(_vertices.begin(), _vertices.end());
	std::vector<glm::vec3>	vertNorms(_vertNorms.begin(), _vertNorms.end());
	std::vector<glm::vec3>	vertNorms1(_vertices.size());
	std::list<glm::vec3>	vertNorms2;
	std::vector<glm::vec2>	texCoords(_texCoords.begin(), _texCoords.end());
	std::vector<glm::vec2>	texCoords1(_vertices.size());
	std::list<glm::vec2>		texCoords2;
	std::list<glm::vec<3, uint>>::iterator	itt;
	std::list<glm::vec<3, uint>>::iterator	itn;

	if (_texCoords.size())
	{
		itt = _texIndices.begin();
		for (glm::vec<3, uint> &idx : _indices)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				unsigned int	vIdx = idx[i];
				unsigned int	tIdx = (*itt)[i];

				texCoords1[vIdx] = texCoords[tIdx];
			}
			itt++;
		}
	}

	itt = _texIndices.begin();
	itn = _normIndices.begin();
	for (glm::vec<3, uint> &idx : _indices)
	{
		glm::vec3	&v1 = vertices[idx.x];
		glm::vec3	&v2 = vertices[idx.y];
		glm::vec3	&v3 = vertices[idx.z];
		glm::vec3	normCalc;

		glm::vec3	edge1(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
		glm::vec3	edge2(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);

		normCalc.x = edge1.y * edge2.z - edge1.z * edge2.y;
		normCalc.y = edge1.z * edge2.x - edge1.x * edge2.z;
		normCalc.z = edge1.x * edge2.y - edge1.y * edge2.x;

		for (unsigned int i = 0; i < 3; i++)
		{
			unsigned int	vIdx = idx[i];
			unsigned int	nIdx = (*itn)[i];
			glm::vec3			&n = vertNorms1[vIdx];
			glm::vec3			norm;

			if (nIdx < vertNorms.size())
				norm = vertNorms[nIdx];
			else
				norm = normCalc;

			if (glm2::length(n) <= 0.0000001f)
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
				idx[i] = (unsigned int)_vertices.size();
				_vertices.push_back(vertices[vIdx]);
				vertNorms2.push_back(norm);
				if (_texCoords.size())
					texCoords2.push_back(texCoords[(*itt)[i]]);
			}
		}
		itt++;
		itn++;
	}

	_vertNorms.clear();
	for (glm::vec3 &norm : vertNorms1)
		_vertNorms.push_back(norm);
	for (glm::vec3 &norm : vertNorms2)
		_vertNorms.push_back(norm);

	for (glm::vec3 &norm : _vertNorms)
		norm *= Q_rsqrt(glm2::dot(norm, norm));

	_texCoords.clear();
	for (glm::vec2 &tex : texCoords1)
		_texCoords.push_back(tex);
	for (glm::vec2 &tex : texCoords2)
		_texCoords.push_back(tex);

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
