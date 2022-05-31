#ifndef SCOP_FACE_HPP
#define SCOP_FACE_HPP

#include <vector>

class Face
{
private:
	std::vector<unsigned int> vertexIDs;

public:
	std::vector<unsigned int> const & getVertexIDs() const;
	void addVertex(unsigned int id);
	std::vector<Face> getTriangulatedFaces() const;

	Face();
	~Face();

};

#endif
