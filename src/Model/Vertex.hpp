#ifndef SCOP_VERTEX_HPP
#define SCOP_VERTEX_HPP

#include "../Vector.hpp"

class Vertex
{
private:
	Vector position;

public:
	Vector getPosition() const;
	void setPosition(Vector position);

	Vertex(Vector position);
	~Vertex();

};

#endif
