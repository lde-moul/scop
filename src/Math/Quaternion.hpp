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
	Quaternion conjugate() const;
	Quaternion invert() const;
	float dot(Quaternion const & other);
	Quaternion slerp(Quaternion const & other, float amount);
	Quaternion slerp(float amount);
	float getAngle() const;
	Quaternion operator+(Quaternion const & other) const;
	Quaternion operator-(Quaternion const & other) const;
	Quaternion operator*(Quaternion const & other) const;
	Quaternion operator*(float other) const;

	Quaternion(float x, float y, float z, float w);
	Quaternion();
	~Quaternion();

};

#endif
