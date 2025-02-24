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
