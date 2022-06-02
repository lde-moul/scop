#include "Vertex.hpp"

Vector Vertex::getPosition() const
{
    return position;
}

void Vertex::setPosition(Vector position)
{
    this->position = position;
}

Vertex::Vertex(Vector position) : position(position) {}

Vertex::~Vertex() {}
