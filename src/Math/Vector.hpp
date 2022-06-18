#ifndef SCOP_VECTOR_HPP
#define SCOP_VECTOR_HPP

class Vector
{
public:
	float x;
	float y;
	float z;
	float w;

	float getLength() const;
	Vector normalize() const;
	Vector operator+(Vector const & other) const;
	Vector operator-(Vector const & other) const;
	Vector operator*(float other) const;
	Vector operator/(float other) const;

	Vector(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f);
	~Vector();

};

#endif
