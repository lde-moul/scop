#ifndef SCOP_VECTOR_HPP
#define SCOP_VECTOR_HPP

class Vector
{
public:
	float x;
	float y;
	float z;
	float w;

	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	Vector operator+(Vector const & other) const;
	Vector operator-(Vector const & other) const;
	Vector operator*(float other) const;
	Vector operator/(float other) const;
	void dump();

	Vector(float x, float y, float z, float w);
	Vector(float x, float y, float z);
	Vector();
	~Vector();

};

#endif
