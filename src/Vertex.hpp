#ifndef SCOP_VERTEX_HPP
#define SCOP_VERTEX_HPP

class Vertex
{
private:
	double x;
	double y;
	double z;

public:
	double getX() const;
	double getY() const;
	double getZ() const;

	Vertex(double x, double y, double z);
	~Vertex();

};

#endif
