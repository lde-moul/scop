#include "Vector.hpp"

#include <iostream> // !!!

float Vector::getX() const
{
    return x;
}

float Vector::getY() const
{
    return y;
}

float Vector::getZ() const
{
    return z;
}

float Vector::getW() const
{
    return w;
}

Vector Vector::operator+(Vector const & other) const
{
	return Vector(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector Vector::operator-(Vector const & other) const
{
	return Vector(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector Vector::operator*(float other) const
{
	return Vector(x * other, y * other, z * other, w * other);
}

Vector Vector::operator/(float other) const
{
	return Vector(x / other, y / other, z / other, w / other);
}

void Vector::dump()
{
	std::cout << x << " " << y << " " << z << " " << w << std::endl;
}

Vector::Vector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector::~Vector() {}
