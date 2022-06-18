#include "Matrix.hpp"

#include <cmath>

Matrix Matrix::translation(float x, float y, float z)
{
	Matrix matrix(true);

	matrix(0, 3) = x;
	matrix(1, 3) = y;
	matrix(2, 3) = z;

	return matrix;
}

Matrix Matrix::scaling(float x, float y, float z)
{
	Matrix matrix(true);

	matrix(0, 0) = x;
	matrix(1, 1) = y;
	matrix(2, 2) = z;

	return matrix;
}

Matrix Matrix::perspective(float fov, float aspectRatio, float near, float far)
{
	Matrix matrix;
	float depth = far - near;
	float fovTan = std::tan(fov / 2);

	matrix(0, 0) = 1 / (aspectRatio * fovTan);
	matrix(1, 1) = 1 / fovTan;
	matrix(2, 2) = (far + near) / depth;
	matrix(2, 3) = (2 * far * near) / depth;
	matrix(3, 2) = -1.f;

	return matrix;
}

float const * Matrix::getArray() const
{
	return &matrix[0][0];
}

float Matrix::operator()(size_t row, size_t column) const
{
	return matrix[row][column];
}

float & Matrix::operator()(size_t row, size_t column)
{
	return matrix[row][column];
}

Matrix Matrix::operator*(Matrix const & other) const
{
	Matrix result;

	for (size_t r = 0; r < 4; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			for (size_t i = 0; i < 4; i++)
			{
				result.matrix[r][c] += matrix[r][i] * other.matrix[i][c];
			}
		}
	}

	return result;
}

Matrix::Matrix(bool identity)
{
	for (size_t r = 0; r < 4; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			matrix[r][c] = 0.f;
		}
	}

	if (identity)
	{
		for (size_t i = 0; i < 4; i++)
		{
			matrix[i][i] = 1.f;
		}
	}
}

Matrix::~Matrix() {}
