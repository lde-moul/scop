#ifndef SCOP_MATRIX_HPP
#define SCOP_MATRIX_HPP

#include <cstddef>

class Matrix
{
private:
	float matrix[4][4];

public:
	static Matrix translation(float x, float y, float z);
	static Matrix scaling(float x, float y, float z);
	static Matrix perspective(float fov, float aspectRatio, float near, float far);

	float const * getArray() const;
	float operator()(size_t row, size_t column) const;
	float & operator()(size_t row, size_t column);
	Matrix operator*(Matrix const & other) const;
	void dump();

	Matrix(bool identity = false);
	~Matrix();

};

#endif
