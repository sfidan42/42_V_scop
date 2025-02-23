#include <Vertex.hpp>

Vertex::Vertex(void) : x(0), y(0), z(0) {};

Vertex::Vertex(float x, float y, float z) : x(x), y(y), z(z) {};

Vertex::Vertex(const Vertex &other) : x(other.x), y(other.y), z(other.z) {};

Vertex &Vertex::operator=(const Vertex &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return (*this);
}

Vertex::~Vertex(void) {};

Vertex operator+(const Vertex &a, const Vertex &b)
{
    Vertex c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return (c);
}