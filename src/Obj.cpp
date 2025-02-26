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

void	Obj::stats(const char *title)
{
	std::size_t	objSize;

	std::cout << title << std::endl;
	std::cout << "\tnumber of _vertices: " << _vertices.size() << std::endl;
	std::cout << "\tnumber of _vertNorms: " << _vertNorms.size() << std::endl;
	std::cout << "\tnumber of _indices: " << _indices.size() << std::endl;
	std::cout << "\tnumber of _texCoords: " << _texCoords.size() << std::endl;
	std::cout << "\tnumber of _texIndices: " << _texIndices.size() << std::endl;
	std::cout << "\t _vertexAvg: " << _vertexAvg.x << " " << _vertexAvg.y << " " << _vertexAvg.z << std::endl;
	objSize = 0;
	objSize += _vertices.size() * sizeof(Vertex);
	objSize += _vertNorms.size() * sizeof(Vertex);
	objSize += _indices.size() * sizeof(uIndex);
	objSize += _texCoords.size() * sizeof(Vertex);
	objSize += _texIndices.size() * sizeof(uIndex);
	std::cout << "\tsize of the object: ";
	if (objSize < 1024)
		std::cout  << objSize / (1024.0f) << "kB";
	else
		std::cout  << objSize / (1024.0f * 1024.0f) << "MB";
	std::cout << std::endl;
}
