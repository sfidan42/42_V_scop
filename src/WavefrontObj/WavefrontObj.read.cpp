#include <WavefrontObj.hpp>

static int	similarity(const vec3 &v1, const vec3 &v2)
{
	float	ans;

	ans = dot(v1, v2);
	ans *= Q_rsqrt(dot(v1, v1));
	ans *= Q_rsqrt(dot(v2, v2));
	ans = acosf(ans);
	ans *= 180.0f / M_PI;
	return (ans < 30.0f);
}

void	WavefrontObj::read(const string &objPath, const string &mtlPath)
{
	{
		ifstream		objFile(objPath);
		string			line;
		vec3			vert;
		vec2			tex;
		vec<3, uint>	idx;
		vec<3, uint>	texIdx;
		vec<3, uint>	normIdx;
		tMaterial		mat;

		if (!objFile.is_open())
		{
			cerr << "could not open file: " << objPath << endl;
			return ;
		}
		_vertices.clear();
		_texCoords.clear();
		_vertNorms.clear();
		_indices.clear();
		_texIndices.clear();
		_normIndices.clear();
		while (getline(objFile, line))
		{
			istringstream	iss(line);
			string			word;
			iss >> word;
			if (word == "v")
			{
				iss >> vert.x >> vert.y >> vert.z;
				_vertices.push_back(vert);
				_vertexAvg += vert;
			}
			else if (word == "vt")
			{
				iss >> tex.x >> tex.y;
				_texCoords.push_back(tex);
			}
			else if (word == "vn")
			{
				iss >> vert.x >> vert.y >> vert.z;
				_vertNorms.push_back(vert * -1.0f);
			}
			else if (word == "f")
			{
				string		fword[4];
				char			c;

				iss >> fword[0] >> fword[1] >> fword[2] >> fword[3];
				istringstream(fword[0]) >> idx.x >> c >> texIdx.x >> c >> normIdx.x;
				istringstream(fword[1]) >> idx.y >> c >> texIdx.y >> c >> normIdx.y;
				istringstream(fword[2]) >> idx.z >> c >> texIdx.z >> c >> normIdx.z;
				idx -= 1;
				texIdx -= 1;
				normIdx -= 1;
				_indices.push_back(idx);
				_texIndices.push_back(texIdx);
				_normIndices.push_back(normIdx);
				if (fword[3].size())
				{
					idx.y = idx.z;
					texIdx.y = texIdx.z;
					normIdx.y = normIdx.z;
					istringstream(fword[3]) >> idx.z >> c >> texIdx.z >> c >> normIdx.z;
					idx.z -= 1;
					texIdx.z -= 1;
					normIdx.z -= 1;
					_indices.push_back(idx);
					_texIndices.push_back(texIdx);
					_normIndices.push_back(normIdx);
				}
			}
		}
		_vertexAvg *= 1.0f / _vertices.size();
	}
	this->stats(objPath.c_str());
	{
		vector<vec3>	vertices(_vertices.begin(), _vertices.end());
		vector<vec3>	vertNorms(_vertNorms.begin(), _vertNorms.end());
		vector<vec3>	vertNorms1(_vertices.size());
		list<vec3>		vertNorms2;
		vector<vec2>	texCoords(_texCoords.begin(), _texCoords.end());
		vector<vec2>	texCoords1(_vertices.size());
		list<vec2>		texCoords2;

		if (_texCoords.size())
		{
			auto itt = _texIndices.begin();
			for (auto &idx : _indices)
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

		auto itt = _texIndices.begin();
		auto itn = _normIndices.begin();
		for (auto &idx : _indices)
		{
			vec3	&v1 = vertices[idx.x];
			vec3	&v2 = vertices[idx.y];
			vec3	&v3 = vertices[idx.z];

			vec3	edge1 = v3 - v1;
			vec3	edge2 = v2 - v1;
			vec3	normCalculated = cross(edge1, edge2);

			for (unsigned int i = 0; i < 3; i++)
			{
				unsigned int	vIdx = idx[i];
				unsigned int	nIdx = (*itn)[i];
				vec3		&n = vertNorms1[vIdx];
				vec3		norm;

				if (nIdx < vertNorms.size())
					norm = vertNorms[nIdx];
				else
					norm = normCalculated;

				if (length(n) <= 0.0000001f)
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
		for (vec3 &norm : vertNorms1)
			_vertNorms.push_back(norm);
		for (vec3 &norm : vertNorms2)
			_vertNorms.push_back(norm);

		for (vec3 &norm : _vertNorms)
			norm *= Q_rsqrt(dot(norm, norm));

		_texCoords.clear();
		for (vec2 &tex : texCoords1)
			_texCoords.push_back(tex);
		for (vec2 &tex : texCoords2)
			_texCoords.push_back(tex);
	}
	this->stats(objPath.c_str());
	{
		ifstream	mtlFile(mtlPath);
		string		line;

		if (!mtlFile.is_open())
		{
			cout << "could not open .mtl file" << endl;
			cout << "using the default material" << endl;
			return ;
		}
		while (getline(mtlFile, line))
		{
			if (line.size() == 0)
				continue ;
			istringstream	iss(line);
			string			word;

			iss >> word;
			if (word == "Kd")
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
				cout << "unknown word: " << word << endl;
		}
	}
}
