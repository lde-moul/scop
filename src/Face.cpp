#include "Face.hpp"

void Face::addVertex(size_t id)
{
	vertexIDs.push_back(id);
}

Face::Face() {}

Face::~Face() {}
