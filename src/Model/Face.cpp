#include "Face.hpp"

std::vector<unsigned int> const & Face::getVertexIDs() const
{
	return vertexIDs;
}

void Face::addVertex(unsigned int id)
{
	vertexIDs.push_back(id);
}

std::vector<Face> Face::getTriangulatedFaces() const
{
	std::vector<Face> subFaces;

	Face face1;
	face1.addVertex(vertexIDs[0]);
	face1.addVertex(vertexIDs[1]);
	face1.addVertex(vertexIDs[2]);
	subFaces.push_back(std::move(face1));

	if (vertexIDs.size() == 4)
	{
		Face face2;
		face2.addVertex(vertexIDs[2]);
		face2.addVertex(vertexIDs[3]);
		face2.addVertex(vertexIDs[0]);
		subFaces.push_back(std::move(face2));
	}

	return subFaces;
}

Face::Face() {}

Face::~Face() {}
