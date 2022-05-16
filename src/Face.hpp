#ifndef SCOP_FACE_HPP
#define SCOP_FACE_HPP

#include <vector>

class Face
{
private:
	std::vector<size_t> vertexIDs;

public:
	void addVertex(size_t id);

	Face();
	~Face();

};

#endif
