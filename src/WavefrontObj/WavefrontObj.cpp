#include <WavefrontObj.hpp>

WavefrontObj::WavefrontObj(void) : _vertexAvg{0.0f, 0.0f, 0.0f}
{
	_mat.kd = glm2::vec3(1.0f, 1.0f, 1.0f);
	_mat.ka = glm2::vec3(0.1f, 0.1f, 0.1f);
	_mat.ks = glm2::vec3(0.7f, 0.7f, 0.7f);
}

WavefrontObj::~WavefrontObj()
{
}

void	WavefrontObj::stats(const char *title)
{
	std::cout << title << std::endl;
	std::cout << "\tnumber of _vertices: " << _vertices.size() << std::endl;
	std::cout << "\tnumber of _vertNorms: " << _vertNorms.size() << std::endl;
	std::cout << "\tnumber of _indices: " << _indices.size() << std::endl;
	std::cout << "\tnumber of _texCoords: " << _texCoords.size() << std::endl;
	std::cout << "\tnumber of _texIndices: " << _texIndices.size() << std::endl;
	std::cout << "\t _vertexAvg: " << _vertexAvg.x << " " << _vertexAvg.y << " " << _vertexAvg.z << std::endl;
}
