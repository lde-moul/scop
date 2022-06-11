#include "Vertex.hpp"

Vector Vertex::getPosition() const
{
    return position;
}

void Vertex::setPosition(Vector position)
{
    this->position = position;
}

Vector Vertex::getTextureCoordinates() const
{
    return textureCoordinates;
}

void Vertex::setTextureCoordinates(Vector coordinates)
{
    this->textureCoordinates = coordinates;
}

Vertex::Vertex(Vector position) : position(position) {}

Vertex::~Vertex() {}
