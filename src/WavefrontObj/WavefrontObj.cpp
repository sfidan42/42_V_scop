#include <WavefrontObj.hpp>

WavefrontObj::WavefrontObj(void) : _vertexAvg(0.0f, 0.0f, 0.0f)
{
	_mat.kd = vec3(1.0f, 1.0f, 1.0f);
	_mat.ka = vec3(0.1f, 0.1f, 0.1f);
	_mat.ks = vec3(0.7f, 0.7f, 0.7f);
}

WavefrontObj::~WavefrontObj()
{
}

void	WavefrontObj::stats(const char *title)
{
	cout << title << endl;
	cout << "\tnumber of _vertices: "	<< _vertices.size()		<< endl;
	cout << "\tnumber of _vertNorms: "	<< _vertNorms.size()	<< endl;
	cout << "\tnumber of _indices: "	<< _indices.size()		<< endl;
	cout << "\tnumber of _texCoords: "	<< _texCoords.size()	<< endl;
	cout << "\tnumber of _texIndices: "<< _texIndices.size()	<< endl;
	cout << "\t _vertexAvg: "
			<< _vertexAvg.x << " "
			<< _vertexAvg.y << " "
			<< _vertexAvg.z << endl;
}
