#ifndef SCOP_VERTEX_HPP
#define SCOP_VERTEX_HPP

#include "../Math/Vector.hpp"

class Vertex
{
private:
	Vector position;
	Vector textureCoordinates;

public:
	Vector getPosition() const;
	void setPosition(Vector position);
	Vector getTextureCoordinates() const;
	void setTextureCoordinates(Vector coordinates);

	Vertex(Vector position);
	~Vertex();

};

#endif
