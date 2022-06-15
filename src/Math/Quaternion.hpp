#ifndef SCOP_QUATERNION_HPP
#define SCOP_QUATERNION_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	static Quaternion getRotation(Vector axis, float angle);

	Matrix getMatrix() const;
	Quaternion normalize() const;
	Quaternion operator*(Quaternion const & other) const;
	void dump();

	Quaternion(float x, float y, float z, float w);
	Quaternion();
	~Quaternion();

};

#endif
