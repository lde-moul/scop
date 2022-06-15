#include "Quaternion.hpp"

#include <cmath>

#include <iostream> // !!!

Quaternion Quaternion::getRotation(Vector axis, float angle)
{
	axis = axis.normalize();
	angle /= 2;

	return Quaternion(
		axis.x * std::sin(angle),
		axis.y * std::sin(angle),
		axis.z * std::sin(angle),
		std::cos(angle)
	);
}

float Quaternion::getX() const
{
	return x;
}

float Quaternion::getY() const
{
	return y;
}

float Quaternion::getZ() const
{
	return z;
}

float Quaternion::getW() const
{
	return w;
}

Matrix Quaternion::getMatrix() const
{
	Matrix matrix;

	matrix(0, 0) = 1 - 2 * y * y - 2 * z * z;
	matrix(0, 1) = 2 * x * y - 2 * z * w;
	matrix(0, 2) = 2 * x * z + 2 * y * w;

	matrix(1, 0) = 2 * x * y + 2 * z * w;
	matrix(1, 1) = 1 - 2 * x * x - 2 * z * z;
	matrix(1, 2) = 2 * y * z - 2 * x * w;

	matrix(2, 0) = 2 * x * z - 2 * y * w;
	matrix(2, 1) = 2 * y * z + 2 * x * w;
	matrix(2, 2) = 1 - 2 * x * x - 2 * y * y;

	matrix(3, 3) = 1;

	return matrix;
}

Quaternion Quaternion::normalize() const
{
	float squaredLength = x * x + y * y + z * z + w * w;

	if (std::abs(squaredLength - 1.f) > 0.001f)
	{
		float length = std::sqrt(squaredLength);
		return Quaternion(
			x / length,
			y / length,
			z / length,
			w / length
		);
	}
	else
	{
		return *this;
	}
}

Quaternion Quaternion::operator*(Quaternion const & other) const
{
	return Quaternion(
		w * other.x + x * other.w + y * other.z - z * other.y,
		w * other.y - x * other.z + y * other.w + z * other.x,
		w * other.z + x * other.y - y * other.x + z * other.w,
		w * other.w - x * other.x - y * other.y - z * other.z
	).normalize();
}

void Quaternion::dump()
{
	std::cout << x << " " << y << " " << z << " " << w << std::endl;
}

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion() : Quaternion(0, 0, 0, 1) {}

Quaternion::~Quaternion() {}
