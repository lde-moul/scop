#include "Vertex.hpp"

double Vertex::getX() const
{
    return x;
}

double Vertex::getY() const
{
    return y;
}

double Vertex::getZ() const
{
    return z;
}

Vertex::Vertex(double x, double y, double z) : x(x), y(y), z(z) {}

Vertex::~Vertex() {}
