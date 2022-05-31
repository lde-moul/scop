#include "Matrix.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>
#include <iostream>

using std::cout;
using std::endl;

void test()
{
	Matrix a;
	a(0, 0) = 9; a(0, 1) = 6; a(0, 2) = 4; a(0, 3) = 4;
	a(1, 0) = 7; a(1, 1) = 1; a(1, 2) = 4; a(1, 3) = 3;
	a(2, 0) = 2; a(2, 1) = 4; a(2, 2) = 5; a(2, 3) = 0;
	a(3, 0) = 3; a(3, 1) = 9; a(3, 2) = 1; a(3, 3) = 8;

	Matrix b;
	b(0, 0) = 3; b(0, 1) = 0; b(0, 2) = 9; b(0, 3) = 5;
	b(1, 0) = 2; b(1, 1) = 7; b(1, 2) = 7; b(1, 3) = 4;
	b(2, 0) = 5; b(2, 1) = 0; b(2, 2) = 1; b(2, 3) = 1;
	b(3, 0) = 8; b(3, 1) = 4; b(3, 2) = 5; b(3, 3) = 5;

	(a * b).dump();
}
